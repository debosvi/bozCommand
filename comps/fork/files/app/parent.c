
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <uv.h>

typedef struct {
    uv_process_t    child_req;
    uv_timer_t      timer_req;
    char*           name;
    uv_loop_t*      loop;
    uv_pipe_t       ios_req[2];
} my_child_t;

static int child_start(my_child_t* p_child);
static uv_timer_t time_wr;

#define DEBUGPRINTF(fmt, ...)   do { fprintf(stderr, fmt "\n", ##__VA_ARGS__); fflush(stderr); } while (0)

#define ALLOWS_FDPASSING    0

#define memory_error(fmt, ...) \
    do { \
        fprintf(stderr, "%s: %s (%d): not enough memory: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

static int my_child_init(my_child_t *ch, char *name, uv_loop_t *loop) {
    if(!ch) return 1;
    if(!name) return 1;
    
    
    // ch->child_req = { 0 };
    ch->name = name;
    if(!loop) ch->loop = uv_default_loop();
    
    if(uv_timer_init(ch->loop, &ch->timer_req)) return 1;
    ch->timer_req.data=ch;
    return 0;
}

static void child_on_timer(uv_timer_t* handle) {
    DEBUGPRINTF("%s: start\n", __FUNCTION__);
    my_child_t* p_child=(my_child_t*)handle->data;
    
    if(child_start(handle->data)) {
        fprintf(stderr, "Unable to start child\n");  
        uv_stop(p_child->loop);
    }
}

static const char* msg = "Toto is dead!";

static void on_write_done(uv_write_t* req, int status) {
    if (status) {
        DEBUGPRINTF("uv_write error: %s\n", uv_strerror(status));
    }

    /* Free the read/write buffer and the request */
    free(req);

}

static void write_to_child(uv_timer_t* handle) {
    int r=0;
    DEBUGPRINTF("%s: start\n", __FUNCTION__);
    
    if(!handle) return;  
    my_child_t* mc=handle->data;   
    if(!mc) return;        
        
    uv_write_t *req=malloc(sizeof(uv_write_t));
    if(!req){    // New request must be allocated as well as ...
        memory_error();                         // ... a buffer of nread size
    }                                           // Don't want to send BUFFER_LEN bytes
    void *p=malloc(strlen(msg)+10);
    if(!p) memory_error();
    
    uv_buf_t buffer = uv_buf_init(p, strlen(msg));
    memcpy(buffer.base, msg, strlen(msg));
    req->data = buffer.base;
    r=uv_write(req, (uv_stream_t*)&mc->ios_req[0], &buffer, 1, on_write_done);
    if(r<0) {
        DEBUGPRINTF("%s: write error, reason(%s)", __FUNCTION__, uv_strerror(r));
    }

    DEBUGPRINTF("%s: continue\n", __FUNCTION__);
}

static void child_on_exit(uv_process_t *req, int64_t exit_status, int term_signal) {
    DEBUGPRINTF("Process exited with status (%I64d), signal (%d)\n", exit_status, term_signal);
    
    my_child_t* mc=req->data;    
    if(!mc) {
        fprintf(stderr, "Bad handle data\n");
        return ;
    }
    
    uv_close((uv_handle_t*)&mc->ios_req[0], 0);
    uv_close((uv_handle_t*)&mc->ios_req[1], 0);
    
    if(uv_timer_start(&mc->timer_req, child_on_timer, 1000, 0)) {
        DEBUGPRINTF("Unable to restart child\n");
        return ;
    }
    
    uv_close((uv_handle_t*) req, NULL);
}

int child_start(my_child_t* p_child) {
    uv_process_options_t options = {0};
    uv_stdio_container_t child_stdio[3];
    int r=0;
    char *args[2];
    
    if(!p_child) return 1;
    
    DEBUGPRINTF("%s: again\n", __FUNCTION__);
    
    args[0] = p_child->name;
    args[1] = 0;
    
    // if(pipe(&l_rpipe[0]))<0)  {
        // fprintf(stderr, "%s: pipe error, reason (%d/%s)\n", errno, strerror(errno));
        // return 1;
    // } 
    
    // if(pipe(&l_rpipe[0]))<0)  {
        // fprintf(stderr, "%s: pipe error, reason (%d/%s)\n", errno, strerror(errno));
        // return 1;
    // }
    
    options.stdio_count = 3;
    memset(&child_stdio, 0, sizeof(uv_stdio_container_t));
    
    if(uv_pipe_init(p_child->loop, &p_child->ios_req[0], ALLOWS_FDPASSING)) return 1;
    if(uv_pipe_init(p_child->loop, &p_child->ios_req[1], ALLOWS_FDPASSING)) return 1;
    
    child_stdio[0].flags = UV_CREATE_PIPE | UV_READABLE_PIPE;
    child_stdio[0].data.stream = (uv_stream_t*)&p_child->ios_req[0];
    child_stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
    child_stdio[1].data.stream = (uv_stream_t*)&p_child->ios_req[1];
    child_stdio[2].flags = UV_INHERIT_FD;
    child_stdio[2].data.fd = 2;
    
    options.stdio = child_stdio;
    options.exit_cb = child_on_exit;
    options.file = args[0];
    options.args = args;

    if ((r = uv_spawn(p_child->loop, &p_child->child_req, &options))) {
        DEBUGPRINTF("Spawn error, reason(%s)\n", uv_strerror(r));
        return 1;
    }
    
    p_child->child_req.data=p_child;    
            
    {
        if(uv_timer_init(p_child->loop, &time_wr)) return 1;
        
        time_wr.data=p_child;
        if(uv_timer_start(&time_wr, write_to_child, 1000, 1000)<0) {
            DEBUGPRINTF("Unable to start write timer\n");
            return 1;
        }
    }
        
    return 0;
}

int main(int ac, char **av) {
    int r=0;
    uv_loop_t *loop = 0;
    my_child_t mc;

    
    (void)ac; 
    (void)av;
    
    loop = uv_default_loop();

    uv_loop_init(loop);
    
    if(my_child_init(&mc, (char*)"child.exe", 0)) {
        DEBUGPRINTF("Unable to init child structure\n");
        return 1;
    }
    
    if(uv_timer_start(&mc.timer_req, child_on_timer, 0, 0)<0) {
        DEBUGPRINTF("Unable to initiate first child start phase\n");
        return 1;
    }

    // while(!r) {
        r=uv_run(loop, UV_RUN_DEFAULT);
        DEBUGPRINTF("loop, exit (%d)\n", r);
        // break;
        // sleep(1);
    // }

    DEBUGPRINTF("Now quitting.\n");
    uv_loop_close(loop);

    return 0;
}
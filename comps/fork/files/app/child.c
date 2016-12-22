
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <uv.h>

#define check_uv(status) \
    do { \
        int code = (status); \
        if(code < 0){ \
            fprintf(stderr, "%s(%d): %s\n", uv_err_name(code), __LINE__, uv_strerror(code)); \
            exit(code); \
        } \
    } while(0)
        
#define memory_error(fmt, ...) \
    do { \
        fprintf(stderr, "%s: %s (%d): not enough memory: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); \
    } while (0)

#define BUFFER_LEN  (4096)

#define DEBUGPRINTF(fmt, ...)   do { fprintf(stderr, fmt "\n", ##__VA_ARGS__); fflush(stderr); } while (0)

static uv_pipe_t stdin_pipe;              // Standard input handle
static uv_pipe_t stdout_pipe;             // Standard output handle

static uv_buf_t read_buffer;              // TCP read buffer
static uv_buf_t write_buffer;             // TCP write buffer
static uv_loop_t *loop = 0;

// Buffer allocation for stdin reads / TCP writes
// There's no need to allocate a new buffer every time, so the global one is reused
static void on_alloc_stdin(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    (void) handle;
    (void) suggested_size;
    *buf = read_buffer;
}

static void on_write_done(uv_write_t* req, int status) {
    if (status) {
        DEBUGPRINTF("uv_write error: %s\n", uv_strerror(status));
    }

    /* Free the read/write buffer and the request */
    free(req);

}

// Callback for a read on stdin
static void on_stdin_read(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf){
    (void) stream;
    (void) buf;

    if (nread > 0){                                 // Valid data is read
        DEBUGPRINTF("%s: read data\n", __FUNCTION__);
        
        if(strncmp(buf->base, "EOF", 3)) {
            uv_write_t *req;
            if(!(req = malloc(sizeof(uv_write_t)))){    // New request must be allocated as well as ...
                memory_error();                         // ... a buffer of nread size
            }                                           // Don't want to send BUFFER_LEN bytes
            uv_buf_t buffer = uv_buf_init(malloc(nread), nread);
            memcpy(buffer.base, buf->base, nread);
            req->data = buffer.base;
            check_uv(uv_write(req, (uv_stream_t*)&stdout_pipe, &buffer, 1, on_write_done)); // Write to the TCP socekt
        }
        else {
            DEBUGPRINTF("%s: child quit\n", __FUNCTION__);
            uv_stop(loop);
        }
    } else if (nread < 0) {                         // EOF is probably read -- the pipe is closed
        DEBUGPRINTF("%s: read error\n", __FUNCTION__);
        if (nread == UV_EOF){
            uv_stop(loop);
        }
    }
}

int main(int ac, char **av) {

    char *buffer=0;

    (void)ac;
    
    loop=uv_default_loop();  
    uv_loop_init(loop);  
    

    if(!(buffer = malloc(BUFFER_LEN))){
        memory_error("Unable to allocate buffer of size %d", BUFFER_LEN);
    }
    read_buffer = uv_buf_init(buffer, BUFFER_LEN);
    
    if(!(buffer = malloc(BUFFER_LEN))){
        memory_error("Unable to allocate buffer of size %d", BUFFER_LEN);
    }
    write_buffer = uv_buf_init(buffer, BUFFER_LEN);
    
    check_uv(uv_pipe_init(loop, &stdin_pipe, 0));
    check_uv(uv_pipe_open(&stdin_pipe, 0));         // 0 is stdin
    check_uv(uv_pipe_init(loop, &stdout_pipe, 0));
    check_uv(uv_pipe_open(&stdout_pipe, 1));        // 1 is stdout
    
    // uv_unref((uv_handle_t*)&stdin_pipe);
    // uv_unref((uv_handle_t*)&stdout_pipe);
    
    check_uv(uv_read_start((uv_stream_t*)&stdin_pipe, on_alloc_stdin, on_stdin_read));
    
    DEBUGPRINTF("%s: start loop\n", av[0]);
    uv_run(loop, UV_RUN_DEFAULT);

    DEBUGPRINTF("%s: end loop\n", av[0]);
    uv_loop_close(loop);

    return 0;
}
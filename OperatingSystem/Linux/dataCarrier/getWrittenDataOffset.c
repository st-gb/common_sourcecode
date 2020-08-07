/**see blktrace:
Thread #1 [blktrace] 21105 [core: 0] (Suspended : Step)
start_buts() at blktrace.c:1.102 0x555555557741	
run_tracers() at blktrace.c:2.656 0x555555557741	
main() at blktrace.c:2.791 0x555555557741	

1. fd = my_open(path, O_RDONLY | O_NONBLOCK);
2. ioctl(dpp->fd, BLKTRACESETUP, &buts) in setup_buts()
3. ioctl(dpp->fd, BLKTRACESTART) in start_buts()  #define BLKTRACESTART _IO(0x12,116)
4. start_tracer: pthread_create(..,thread_main,...)
    handle_pfds(...) : handle_pfds_file*/


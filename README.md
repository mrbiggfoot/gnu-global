# gnu-global
GNU Global fork. Additional functionality:
* `-t` flag for `gtags` to use individual file timestamps for incremental update.
* `--print-all <min_len>` option for `global` to print all symbol names of at least the specified length.
* `parallel/pgtags` and `pglobal` scripts for parallelizing gtags DB generation and queries based on the file list splitting.


#ifndef _GTAGS_FILE_TIME_H_
#define _GTAGS_FILE_TIME_H_

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Read contents of dbpath/GTIMES. */
void ft_read(const char *dbpath);

/* Update cached mtime value for file identified by fid.
 * Returns non-zero if mtime is greater than the cached value or if there is no
 * cached value, 0 otherwise. */
int ft_update(int fid, time_t mtime);

/* Write mtime values to dbpath/GTIMES file. */
void ft_write(const char *dbpath);

#ifdef __cplusplus
}
#endif

#endif /* _GTAGS_FILE_TIME_H_ */

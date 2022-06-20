
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "file_time.h"
extern "C" {
#include "die.h"
}

using namespace std;

typedef unordered_map<int, time_t> ft_map_t;
static ft_map_t g_ft_map;

static string ft_name(const char *dbpath) {
  return string(dbpath) + "/GTIMES";
}

void ft_read(const char *dbpath) {
  const string name = ft_name(dbpath);
  FILE *fp = fopen(name.c_str(), "rb");
  if (!fp) {
    die("Failed to open '%s' for read", name.c_str());
  }
  g_ft_map.clear();

  int fid;
  time_t ftime;
  while (fread(&fid, sizeof(fid), 1, fp) == 1) {
    if (fread(&ftime, sizeof(ftime), 1, fp) != 1) {
      die("Invalid file '%s'", name.c_str());
    }
    g_ft_map[fid] = ftime;
  }
  if (!feof(fp)) {
    die("Failed to read from '%s'", name.c_str());
  }

  fclose(fp);
}

int ft_update(int fid, time_t mtime) {
  time_t &old_mtime = g_ft_map[fid];
  int ret = (mtime > old_mtime);
  old_mtime = mtime;
  return ret;
}

void ft_write(const char *dbpath) {
  const string name = ft_name(dbpath);
  FILE *fp = fopen(name.c_str(), "wb");
  if (!fp) {
    die("Failed to open '%s' for write", name.c_str());
  }

  for (ft_map_t::iterator it = g_ft_map.begin(); it != g_ft_map.end(); ++it) {
    if (fwrite(&it->first, sizeof(it->first), 1, fp) != 1) {
      die("Failed to write file id to '%s'", name.c_str());
    }
    if (fwrite(&it->second, sizeof(it->second), 1, fp) != 1) {
      die("Failed to write timestamp to '%s'", name.c_str());
    }
  }

  fclose(fp);
}

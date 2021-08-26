#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>


int main ()  
{  
  int fd, wd;  

  fd = inotify_init1 (IN_NONBLOCK);  

  printf("fd: %d %d\n", fd, errno);  

  wd =
    inotify_add_watch (fd, "/remote_records/",
           IN_MODIFY | IN_CREATE | IN_DELETE |
           IN_CLOSE_WRITE);  

  char buf[4096]
    __attribute__ ((aligned (__alignof__ (struct inotify_event))));
  const struct inotify_event *event;

  int i;

  ssize_t len;
  char *ptr;


  for (;;)
  {
    /* Read some events. */
    len = read (fd, buf, sizeof buf);

    for (ptr = buf; ptr < buf + len;
     ptr += sizeof (struct inotify_event) + event->len)
    {
      event = (const struct inotify_event *) ptr;

      if (event->mask & IN_ISDIR)
        continue;

      if (event->mask & IN_CREATE)
        printf ("Created: %s\n", event->name);
      else if (event->mask & IN_MODIFY)
        printf ("Modified: %s\n", event->name);
      else if (event->mask & IN_DELETE)
        printf ("Deleted: %s\n", event->name);
      else if (event->mask & IN_CLOSE_WRITE)
        printf ("Closed write: %s\n", event->name);
      else
        printf("dunno %s\n", event->name);
    }
  }

  return 0;
}

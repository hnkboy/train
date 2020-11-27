#include<stdio.h>
#include <fcntl.h>		/* for open */
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>		/* for iovec */

static int
vhost_user_init_server_sock (const char *sock_filename, int *sock_fd)
{
  int rv = 0;
  struct sockaddr_un un = { };
  int fd;
  /* create listening socket */
  if ((fd = socket (AF_UNIX, SOCK_STREAM, 0)) < 0)
    return -1;

  un.sun_family = AF_UNIX;
  strncpy ((char *) un.sun_path, (char *) sock_filename,
	   sizeof (un.sun_path) - 1);

  /* remove if exists */
  unlink ((char *) sock_filename);

  if (bind (fd, (struct sockaddr *) &un, sizeof (un)) == -1)
    {
      rv = -1;
      goto error;
    }

  if (listen (fd, 1) == -1)
    {
      rv = -1;
      goto error;
    }

  *sock_fd = fd;
  return 0;

error:
  close (fd);
  return rv;
}
void main()
{
	int fd = -1;
	int rv = 0;
	rv = vhost_user_init_server_sock("/home/jerry/1.socki", &fd);
	printf("retrun value= %d, fd=%d",rv,fd);
}

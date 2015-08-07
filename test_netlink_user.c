#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
 
 
#define NETLINK_NETLINKTEST     22
 
#define NLMSG_TEST_ECHO     0x10
#define NLMSG_TEST_PING     0x11
#define NLMSG_TEST_COMPUTE      0x12
 
#define NLMSG_TEST_ECHO_MAXLEN  100
#define NLMSG_TEST_PING_MAXLEN  100
 
#define NLMSG_TEST_COMPUTE_ADD  0
#define NLMSG_TEST_COMPUTE_SUB  1
#define NLMSG_TEST_COMPUTE_MUL  2
#define NLMSG_TEST_COMPUTE_DIV  3
 
int netlink_test_echo(int fd, struct sockaddr_nl *daddr)
{
    int res;
    int len;
    struct nlmsghdr *nlh;
    char    *msg = "hello worlb";
 
    len = strlen(msg);
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(len + 1));
    if (!nlh) {
        printf("malloc() error.\n");
        return -1;
    }
    nlh->nlmsg_type = NLMSG_TEST_ECHO;
    nlh->nlmsg_flags = NLM_F_REQUEST;
    nlh->nlmsg_seq = 0;
    nlh->nlmsg_pid = getpid();
    strcpy(NLMSG_DATA(nlh), msg);
    nlh->nlmsg_len = NLMSG_LENGTH(len + 1);
 
    res = sendto(fd, nlh, NLMSG_SPACE(len + 1), 0, (struct sockaddr *)daddr, sizeof(struct sockaddr_nl));
    if (res == -1)
        printf("send() error.\n");
    free(nlh);
    return 0;
}
 
int netlink_test_ping(int fd, struct sockaddr_nl *daddr)
{
    int res;
    int len;
    char    buf[40];
    char    *ptr;
    int addr_len = sizeof(struct sockaddr_nl);
    struct nlmsghdr *nlh;
    char    *msg = "hello worlb";
 
    len = strlen(msg);
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(len + 1));
    if (!nlh) {
        printf("malloc() error.\n");
        return -1;
    }
    nlh->nlmsg_type = NLMSG_TEST_PING;
    nlh->nlmsg_flags = NLM_F_REQUEST;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();
    strcpy(NLMSG_DATA(nlh), msg);
    nlh->nlmsg_len = NLMSG_LENGTH(len + 1);
 
    res = sendto(fd, nlh, NLMSG_SPACE(len + 1), 0, (struct sockaddr *)daddr, addr_len);
    if (res == -1) {
        printf("sendto() error.\n");
        goto error;
    }
 
    memset(buf, 0, 40);
    res = recvfrom(fd, buf, 40, 0, (struct sockaddr *)daddr, &addr_len);
    if (res == -1) {
        printf("recvfrom() error.\n");
        goto error;
    }
    ptr = NLMSG_DATA((struct nlmsghdr *)buf);
    len = *(int *)ptr;
    ptr += 4;
    printf("Data: %s  (%d bytes)\n", ptr, len);
 
error:
    free(nlh);
    return res;
}
 
int netlink_test_compute(int fd, struct sockaddr_nl *daddr)
{
    int res;
    char    buf[40];
    int *ptr;
    int addr_len = sizeof(struct sockaddr_nl);
    struct nlmsghdr *nlh;
 
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(12));
    if (!nlh) {
        printf("malloc() error.\n");
        return -1;
    }
    nlh->nlmsg_type = NLMSG_TEST_COMPUTE;
    nlh->nlmsg_flags = NLM_F_REQUEST;
    nlh->nlmsg_seq = 2;
    nlh->nlmsg_pid = getpid();
    ptr = NLMSG_DATA(nlh);
    *ptr++ = NLMSG_TEST_COMPUTE_ADD;
    *ptr++ = 3;
    *ptr = 5;
    nlh->nlmsg_len = NLMSG_LENGTH(12);
 
    res = sendto(fd, nlh, NLMSG_SPACE(12), 0, (struct sockaddr *)daddr, addr_len);
    if (res == -1) {
        printf("sendto() error.\n");
        goto error;
    }
 
    memset(buf, 0, 40);
    res = recvfrom(fd, buf, 40, 0, (struct sockaddr *)daddr, &addr_len);
    if (res == -1) {
        printf("recvfrom() error.\n");
        goto error;
    }
    ptr = NLMSG_DATA((struct nlmsghdr *)buf);
    printf("3 + 5 = %d\n", *ptr);
 
error:
    free(nlh);
    return res;
}
 
int main(int argc, char *argv[])
{
    int fd;
    int res;
    struct sockaddr_nl  saddr, daddr;
 
    fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_NETLINKTEST);
    if (!fd) {
        printf("socket() error.\n");
        return -1;
    }
 
    memset(&saddr, 0, sizeof(saddr));
    saddr.nl_family = AF_NETLINK;
    saddr.nl_pid = getpid();
 
    memset(&daddr, 0, sizeof(daddr));
    daddr.nl_family = AF_NETLINK;
    daddr.nl_pid = 0;
 
    res = bind(fd, (const struct sockaddr *)&saddr, sizeof(saddr));
    if (res == -1) {
        printf("bind() error.\n");
        goto error;
    }
 
    netlink_test_echo(fd, &daddr);
    printf("\n1done\n" );
    netlink_test_ping(fd, &daddr);
    printf("\n2done\n" );
    netlink_test_compute(fd, &daddr);
    printf("\n3done\n" );
error:
    close(fd);
    return res;
}
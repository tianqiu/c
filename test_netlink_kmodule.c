#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
 
MODULE_AUTHOR("Yanchuan Nian");
MODULE_LICENSE("GPL");
 
#define NETLINK_NETLINKTEST 22
 
#define NLMSG_TEST_ECHO     0x10
#define NLMSG_TEST_PING     0x11
#define NLMSG_TEST_COMPUTE  0x12
 
#define NLMSG_TEST_ECHO_MAXLEN  100
#define NLMSG_TEST_PING_MAXLEN  100
 
#define NLMSG_TEST_COMPUTE_ADD  0
#define NLMSG_TEST_COMPUTE_SUB  1
#define NLMSG_TEST_COMPUTE_MUL  2
#define NLMSG_TEST_COMPUTE_DIV  3

static struct sock *nltest_sock;
static struct sock *nltest_sock2;
 
static int nltest_rcv_echo(struct sk_buff *skb, struct nlmsghdr *nlh)
{
    char *buf;
    int len = nlmsg_len(nlh);
 
    if (len > NLMSG_TEST_ECHO_MAXLEN)
        return -ERANGE;
    buf = kzalloc(len + 1, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;
 
    memcpy(buf, nlmsg_data(nlh), len);
    printk(KERN_INFO"Receive msg from userspace: %s\n", buf);
    kfree(buf);
    return 0;
}
 
static int nltest_rcv_ping(struct sk_buff *in_skb, struct nlmsghdr *nlh)
{
    char    *data;
    struct nlmsghdr *rep;
    struct sk_buff  *skb;
    size_t payload = 0;
    int len = nlmsg_len(nlh);
    payload = 4 + len;
    if (len > NLMSG_TEST_PING_MAXLEN)
        return -ERANGE;
    skb = netlink_alloc_skb(in_skb->sk, nlmsg_total_size(payload),
            NETLINK_CB(in_skb).portid, GFP_KERNEL);
    if(!skb)
        return -ENOMEM;
    rep = __nlmsg_put(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
            NLMSG_TEST_PING, payload, 0);
    data = nlmsg_data(rep);
    *(int *)data = len;
    data += 4;
    memcpy(data, nlmsg_data(nlh), len);
    netlink_unicast(in_skb->sk, skb, NETLINK_CB(in_skb).portid, MSG_DONTWAIT);
 
    return 0;
}
 
static int nltest_rcv_compute(struct sk_buff *in_skb, struct nlmsghdr *nlh)
{
    int *ptr;
    int operator;
    int oprand1, oprand2, result;
    struct nlmsghdr *rep;
    struct sk_buff  *skb;
    size_t payload = 4;
    int len = nlmsg_len(nlh);
 
    if (len != 12)
        return -EINVAL;
 
    ptr = (int *)nlmsg_data(nlh);
    operator = *ptr++;
    oprand1 = *ptr++;
    oprand2 = *ptr;
 
    switch (operator) {
    case NLMSG_TEST_COMPUTE_ADD:
        result = oprand1 + oprand2;
        break;
    case NLMSG_TEST_COMPUTE_SUB:
        result = oprand1 - oprand2;
        break;
    case NLMSG_TEST_COMPUTE_MUL:
        result = oprand1 * oprand2;
        break;
    case NLMSG_TEST_COMPUTE_DIV:
        result = oprand1 / oprand2;
        break;
    default:
        return -EINVAL;
    }
 
    skb = netlink_alloc_skb(in_skb->sk, nlmsg_total_size(payload),
            NETLINK_CB(in_skb).portid, GFP_KERNEL);
    if(!skb)
        return -ENOMEM;
    rep = __nlmsg_put(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
            NLMSG_TEST_PING, payload, 0);
    ptr = nlmsg_data(rep);
    *ptr = result;
    netlink_unicast(in_skb->sk, skb, NETLINK_CB(in_skb).portid, MSG_DONTWAIT);
    return 0;
}
 
static int nltest_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
    unsigned short type;
    type = nlh->nlmsg_type;
 
    switch (type) {
    case NLMSG_TEST_ECHO:
        return nltest_rcv_echo(skb, nlh);
    case NLMSG_TEST_PING:
        return nltest_rcv_ping(skb, nlh);
    case NLMSG_TEST_COMPUTE:
        return nltest_rcv_compute(skb, nlh);
    default:
        return -EINVAL;
    }
}
 
static void nltest_rcv(struct sk_buff *skb)
{
  //  NETLINK_CB(skb).portid= 0;
    printk("\n1\n");
    netlink_rcv_skb(skb, &nltest_rcv_msg);
}
 
static void nltest_rcv2(struct sk_buff *skb)
{
    printk("\n2\n");
    netlink_rcv_skb(skb, &nltest_rcv_msg);
}

static int __init netlinktest_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input  = nltest_rcv,
    };
     struct netlink_kernel_cfg cfg2 = {
        .input  = nltest_rcv2,
    };


    nltest_sock = netlink_kernel_create(&init_net, NETLINK_NETLINKTEST, &cfg);
    nltest_sock2= netlink_kernel_create(&init_net, NETLINK_NETLINKTEST, &cfg2);
    if (!nltest_sock)
        return -ENOMEM;
    printk(KERN_INFO"Enter netlink test module.\n");
    return 0;
}
 
static void __exit netlinktest_exit(void)
{
    printk(KERN_INFO"Leave netlink test module.\n");
  //  netlink_kernel_release(so1);
    netlink_kernel_release(nltest_sock);
    netlink_kernel_release(nltest_sock2);
}
 
module_init(netlinktest_init);
module_exit(netlinktest_exit);
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

int pre_routing_state = 0;
int post_routing_state = 1;
EXPORT_SYMBOL( pre_routing_state );
EXPORT_SYMBOL( post_routing_state );

static unsigned int Hook_Func(void *priv,
                  struct sk_buff *skb,
                  const struct nf_hook_state *state)
{
	if(*(int*)priv == pre_routing_state)
	{
		printk(KERN_INFO "Incoming packet detected\n");
	}
	else if(*(int*)priv == post_routing_state)
	{
		printk(KERN_INFO "Outgoing packet detected\n");
	}
	return NF_ACCEPT;
}

/* Структура для регистрации функции перехватчика входящих ip пакетов */
struct nf_hook_ops incoming;
struct nf_hook_ops outgoing;

int Init(void)
{
    printk(KERN_INFO "Start module Shifter\n");

    /* Заполняем структуру для регистрации hook функции */
    /* Указываем имя функции, которая будет обрабатывать пакеты */
    incoming.hook = Hook_Func;
    /* Устанавливаем указатель на модуль, создавший hook */
    //bundle.owner = THIS_MODULE;
    /* Указываем семейство протоколов */
    incoming.pf = PF_INET;
    /* Указываем, в каком месте будет срабатывать функция */
    incoming.hooknum = NF_INET_PRE_ROUTING;
    /* Выставляем самый высокий приоритет для функции */
    incoming.priority = NF_IP_PRI_FIRST;
    /* Передаем в функцию время ее вызова */
    incoming.priv = &pre_routing_state;
    /* Регистрируем */
    nf_register_net_hook(&init_net, &incoming);

    /* Заполняем структуру для регистрации hook функции */
    /* Указываем имя функции, которая будет обрабатывать пакеты */
    outgoing.hook = Hook_Func;
    /* Устанавливаем указатель на модуль, создавший hook */
    //bundle.owner = THIS_MODULE;
    /* Указываем семейство протоколов */
    outgoing.pf = PF_INET;
    /* Указываем, в каком месте будет срабатывать функция */
    outgoing.hooknum = NF_INET_POST_ROUTING;
    /* Выставляем самый высокий приоритет для функции */
    outgoing.priority = NF_IP_PRI_FIRST;
    /* Передаем в функцию время ее вызова */
    outgoing.priv = &post_routing_state;
    /* Регистрируем */
    nf_register_net_hook(&init_net, &outgoing);
    return 0;
}

void Exit(void)
{
    /* Удаляем из цепочки hook функцию */
    nf_unregister_net_hook(&init_net, &incoming);
    nf_unregister_net_hook(&init_net, &outgoing);
    printk(KERN_INFO "End module Shifter\n");
}

module_init(Init);
module_exit(Exit);
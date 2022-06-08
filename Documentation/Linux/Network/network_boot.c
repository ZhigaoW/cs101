/**
 * smpboot_register_percpu_thread - Register a per_cpu thread related to hotplug
 * @plug_thread:	Hotplug thread descriptor
 *
 * Creates and starts the threads on all online cpus.
 */



// --> para smp_hostplug_thread
//
int smpboot_register_percpu_thread(struct smp_hotplug_thread *plug_thread)
{
    unsigned int cpu;
    int ret = 0;

    get_online_cpus();
    mutex_lock(&smpboot_threads_lock);
    for_each_online_cpu(cpu) {
        ret = __smpboot_create_thread(plug_thread, cpu);
        if (ret) {
            smpboot_destroy_threads(plug_thread);
            goto out;
        }
        smpboot_unpark_thread(plug_thread, cpu);
    }
    list_add(&plug_thread->list, &hotplug_threads);
    out:
    mutex_unlock(&smpboot_threads_lock);
    put_online_cpus();
    return ret;
}


static struct smp_hotplug_thread softirq_threads = {
        .store			= &ksoftirqd,
        .thread_should_run	= ksoftirqd_should_run,
        .thread_fn		= run_ksoftirqd,
        .thread_comm		= "ksoftirqd/%u",
};

static __init int spawn_ksoftirqd(void)
{
    register_cpu_notifier(&cpu_nfb);

    BUG_ON(smpboot_register_percpu_thread(&softirq_threads));

    return 0;
}





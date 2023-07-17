cmd_/project/kamv_linked_list.o := arm-linux-gnueabihf-gcc -Wp,-MMD,/project/.kamv_linked_list.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabihf/8/include -I/src/arch/arm/include -I./arch/arm/include/generated -I/src/include -I./include -I/src/arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I/src/include/uapi -I./include/generated/uapi -include /src/include/linux/kconfig.h -include /src/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -fmacro-prefix-map=/src/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-ipa-sra -msoft-float -mabi=aapcs-linux -mfpu=vfp -funwind-tables -marm -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-a -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -O2 --param=allow-store-data-races=0 -Wframe-larger-than=1024 -fstack-protector-strong -Wimplicit-fallthrough -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned  -DMODULE  -DKBUILD_BASENAME='"kamv_linked_list"' -DKBUILD_MODNAME='"kamv_linked_list"' -c -o /project/kamv_linked_list.o /project/kamv_linked_list.c

source_/project/kamv_linked_list.o := /project/kamv_linked_list.c

deps_/project/kamv_linked_list.o := \
  /src/include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /src/include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /src/include/linux/compiler_attributes.h \
  /src/include/linux/compiler-gcc.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/retpoline.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
    $(wildcard include/config/kcov.h) \
  /src/include/linux/cdev.h \
  /src/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /src/include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /src/include/uapi/linux/types.h \
  /src/arch/arm/include/uapi/asm/types.h \
  /src/include/asm-generic/int-ll64.h \
  /src/include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  /src/include/asm-generic/bitsperlong.h \
  /src/include/uapi/asm-generic/bitsperlong.h \
  /src/include/uapi/linux/posix_types.h \
  /src/include/linux/stddef.h \
  /src/include/uapi/linux/stddef.h \
  /src/include/linux/compiler_types.h \
  /src/arch/arm/include/uapi/asm/posix_types.h \
  /src/include/uapi/asm-generic/posix_types.h \
  /src/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /src/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
    $(wildcard include/config/page/poisoning/zero.h) \
  /src/include/linux/const.h \
  /src/include/vdso/const.h \
  /src/include/uapi/linux/const.h \
  /src/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /src/include/linux/limits.h \
  /src/include/uapi/linux/limits.h \
  /src/include/vdso/limits.h \
  /src/include/linux/linkage.h \
    $(wildcard include/config/arch/use/sym/annotations.h) \
  /src/include/linux/stringify.h \
  /src/include/linux/export.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/rel/crcs.h) \
    $(wildcard include/config/have/arch/prel32/relocations.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
    $(wildcard include/config/unused/symbols.h) \
  /src/arch/arm/include/asm/linkage.h \
  /src/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/stack/validation.h) \
  arch/arm/include/generated/asm/rwonce.h \
  /src/include/asm-generic/rwonce.h \
  /src/include/linux/kasan-checks.h \
    $(wildcard include/config/kasan.h) \
  /src/include/linux/kcsan-checks.h \
    $(wildcard include/config/kcsan.h) \
    $(wildcard include/config/kcsan/ignore/atomics.h) \
  /src/include/linux/bitops.h \
  /src/include/linux/bits.h \
  /src/include/vdso/bits.h \
  /src/include/linux/build_bug.h \
  /src/arch/arm/include/asm/bitops.h \
  /src/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /src/include/linux/typecheck.h \
  /src/arch/arm/include/asm/irqflags.h \
    $(wildcard include/config/cpu/v7m.h) \
  /src/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /src/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /src/arch/arm/include/asm/hwcap.h \
  /src/arch/arm/include/uapi/asm/hwcap.h \
  /src/include/asm-generic/irqflags.h \
  /src/arch/arm/include/asm/percpu.h \
    $(wildcard include/config/cpu/v6.h) \
  /src/include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /src/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /src/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
    $(wildcard include/config/amd/mem/encrypt.h) \
  /src/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arm/heavy/mb.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/spectre.h) \
  /src/include/asm-generic/barrier.h \
  /src/include/asm-generic/bitops/non-atomic.h \
  /src/include/asm-generic/bitops/builtin-__fls.h \
  /src/include/asm-generic/bitops/builtin-__ffs.h \
  /src/include/asm-generic/bitops/builtin-fls.h \
  /src/include/asm-generic/bitops/builtin-ffs.h \
  /src/include/asm-generic/bitops/ffz.h \
  /src/include/asm-generic/bitops/fls64.h \
  /src/include/asm-generic/bitops/sched.h \
  /src/include/asm-generic/bitops/hweight.h \
  /src/include/asm-generic/bitops/arch_hweight.h \
  /src/include/asm-generic/bitops/const_hweight.h \
  /src/include/asm-generic/bitops/lock.h \
  /src/include/linux/atomic.h \
  /src/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
    $(wildcard include/config/arm/lpae.h) \
  /src/include/linux/prefetch.h \
  /src/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/binfmt/elf/fdpic.h) \
  /src/arch/arm/include/asm/hw_breakpoint.h \
  /src/arch/arm/include/asm/unified.h \
  /src/arch/arm/include/asm/vdso/processor.h \
    $(wildcard include/config/arm/errata/754327.h) \
  /src/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /src/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
  /src/include/asm-generic/cmpxchg-local.h \
  /src/include/linux/atomic-fallback.h \
  /src/include/asm-generic/atomic-long.h \
  /src/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /src/include/asm-generic/bitops/le.h \
  /src/arch/arm/include/uapi/asm/byteorder.h \
  /src/include/linux/byteorder/little_endian.h \
  /src/include/uapi/linux/byteorder/little_endian.h \
  /src/include/linux/swab.h \
  /src/include/uapi/linux/swab.h \
  /src/arch/arm/include/asm/swab.h \
  /src/arch/arm/include/uapi/asm/swab.h \
  /src/include/linux/byteorder/generic.h \
  /src/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /src/include/linux/kstrtox.h \
  /src/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /src/include/linux/minmax.h \
  /src/include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/quiet.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk/nmi.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/dynamic/debug/core.h) \
  /src/include/linux/init.h \
    $(wildcard include/config/strict/kernel/rwx.h) \
    $(wildcard include/config/strict/module/rwx.h) \
  /src/include/linux/kern_levels.h \
  /src/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /src/include/uapi/linux/kernel.h \
  /src/include/uapi/linux/sysinfo.h \
  /src/include/linux/ratelimit_types.h \
  /src/include/uapi/linux/param.h \
  arch/arm/include/generated/uapi/asm/param.h \
  /src/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /src/include/uapi/asm-generic/param.h \
  /src/include/linux/spinlock_types.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /src/arch/arm/include/asm/spinlock_types.h \
  /src/include/linux/lockdep_types.h \
    $(wildcard include/config/prove/raw/lock/nesting.h) \
    $(wildcard include/config/preempt/lock.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  /src/include/linux/rwlock_types.h \
  /src/include/linux/dynamic_debug.h \
    $(wildcard include/config/jump/label.h) \
  /src/include/linux/jump_label.h \
    $(wildcard include/config/have/arch/jump/label/relative.h) \
  /src/arch/arm/include/asm/jump_label.h \
  /src/arch/arm/include/asm/div64.h \
  /src/arch/arm/include/asm/compiler.h \
  /src/include/asm-generic/div64.h \
  /src/include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  /src/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /src/include/linux/err.h \
  arch/arm/include/generated/uapi/asm/errno.h \
  /src/include/uapi/asm-generic/errno.h \
  /src/include/uapi/asm-generic/errno-base.h \
  /src/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/debug/mutexes.h) \
  arch/arm/include/generated/asm/current.h \
  /src/include/asm-generic/current.h \
  /src/include/linux/thread_info.h \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  /src/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/bug/on/data/corruption.h) \
  /src/arch/arm/include/asm/bug.h \
    $(wildcard include/config/debug/bugverbose.h) \
  /src/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
  /src/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /src/include/linux/instrumentation.h \
    $(wildcard include/config/debug/entry.h) \
  /src/include/linux/restart_block.h \
  /src/include/linux/time64.h \
  /src/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  /src/include/vdso/math64.h \
  /src/include/vdso/time64.h \
  /src/include/uapi/linux/time.h \
  /src/include/uapi/linux/time_types.h \
  /src/include/linux/errno.h \
  /src/include/uapi/linux/errno.h \
  /src/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/stackprotector/per/task.h) \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/arm/thumbee.h) \
  /src/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /src/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/kuser/helpers.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /src/arch/arm/include/asm/glue.h \
  /src/arch/arm/include/asm/pgtable-2level-types.h \
  /src/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/xip/kernel.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/xip/phys/addr.h) \
    $(wildcard include/config/debug/virtual.h) \
  /src/include/linux/sizes.h \
  /src/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /src/include/linux/pfn.h \
  /src/include/asm-generic/getorder.h \
  /src/include/linux/lockdep.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
    $(wildcard include/config/preempt/count.h) \
  /src/include/linux/smp.h \
    $(wildcard include/config/up/late/init.h) \
  /src/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  /src/include/linux/bitmap.h \
  /src/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
    $(wildcard include/config/fortify/source.h) \
  /src/include/uapi/linux/string.h \
  /src/arch/arm/include/asm/string.h \
  /src/include/linux/smp_types.h \
  /src/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /src/include/linux/preempt.h \
    $(wildcard include/config/trace/preempt/toggle.h) \
    $(wildcard include/config/preemption.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/arm/include/generated/asm/preempt.h \
  /src/include/asm-generic/preempt.h \
  /src/arch/arm/include/asm/smp.h \
  /src/include/linux/osq_lock.h \
  /src/include/linux/debug_locks.h \
  /src/include/linux/idr.h \
  /src/include/linux/radix-tree.h \
  /src/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  /src/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  /src/include/linux/rcupdate.h \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tasks/rcu/generic.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/tasks/trace/rcu.h) \
    $(wildcard include/config/tasks/rude/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/arch/weak/release/acquire.h) \
  /src/include/linux/bottom_half.h \
  /src/include/linux/rcutree.h \
  /src/include/linux/spinlock.h \
  arch/arm/include/generated/asm/mmiowb.h \
  /src/include/asm-generic/mmiowb.h \
    $(wildcard include/config/mmiowb.h) \
  /src/arch/arm/include/asm/spinlock.h \
  /src/include/linux/rwlock.h \
    $(wildcard include/config/preempt.h) \
  /src/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /src/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /src/include/linux/xarray.h \
    $(wildcard include/config/xarray/multi.h) \
  /src/include/linux/gfp.h \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/contig/alloc.h) \
    $(wildcard include/config/cma.h) \
  /src/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/shadow/call/stack.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/holes/in/zone.h) \
  /src/include/linux/wait.h \
  /src/include/uapi/linux/wait.h \
  /src/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
    $(wildcard include/config/numa/keep/meminfo.h) \
  /src/include/linux/seqlock.h \
  /src/include/linux/ww_mutex.h \
    $(wildcard include/config/debug/ww/mutex/slowpath.h) \
  /src/include/linux/nodemask.h \
  /src/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /src/include/linux/page-flags-layout.h \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/kasan/sw/tags.h) \
  include/generated/bounds.h \
  /src/include/linux/mm_types.h \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/aufs/fs.h) \
    $(wildcard include/config/userfaultfd.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/have/arch/compat/mmap/bases.h) \
    $(wildcard include/config/membarrier.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/arch/want/batched/unmap/tlb/flush.h) \
    $(wildcard include/config/iommu/support.h) \
  /src/include/linux/mm_types_task.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
  /src/include/linux/auxvec.h \
  /src/include/uapi/linux/auxvec.h \
  /src/arch/arm/include/asm/auxvec.h \
  /src/arch/arm/include/uapi/asm/auxvec.h \
  /src/include/linux/rbtree.h \
  /src/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/debug/rwsems.h) \
  /src/include/linux/completion.h \
  /src/include/linux/swait.h \
  /src/include/linux/uprobes.h \
    $(wildcard include/config/uprobes.h) \
  /src/arch/arm/include/asm/uprobes.h \
  /src/arch/arm/include/asm/probes.h \
  /src/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/wq/watchdog.h) \
  /src/include/linux/timer.h \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/no/hz/common.h) \
  /src/include/linux/ktime.h \
  /src/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
    $(wildcard include/config/posix/timers.h) \
  /src/include/linux/time32.h \
  /src/include/linux/timex.h \
  /src/include/uapi/linux/timex.h \
  /src/arch/arm/include/asm/timex.h \
  /src/include/vdso/time32.h \
  /src/include/vdso/time.h \
  /src/include/linux/jiffies.h \
  /src/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /src/include/vdso/ktime.h \
  /src/include/linux/timekeeping.h \
  /src/include/linux/timekeeping32.h \
  /src/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /src/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
    $(wildcard include/config/vdso.h) \
  /src/include/linux/page-flags.h \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/idle/page/tracking.h) \
    $(wildcard include/config/thp/swap.h) \
    $(wildcard include/config/ksm.h) \
  /src/include/linux/memory_hotplug.h \
    $(wildcard include/config/arch/has/add/pages.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /src/include/linux/notifier.h \
    $(wildcard include/config/tree/srcu.h) \
  /src/include/linux/srcu.h \
    $(wildcard include/config/tiny/srcu.h) \
    $(wildcard include/config/srcu.h) \
  /src/include/linux/rcu_segcblist.h \
  /src/include/linux/srcutree.h \
  /src/include/linux/rcu_node_tree.h \
    $(wildcard include/config/rcu/fanout.h) \
    $(wildcard include/config/rcu/fanout/leaf.h) \
  /src/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/sched/smt.h) \
  /src/include/linux/arch_topology.h \
    $(wildcard include/config/generic/arch/topology.h) \
  /src/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
    $(wildcard include/config/bl/switcher.h) \
  /src/include/asm-generic/topology.h \
  /src/include/linux/kconfig.h \
  /src/include/linux/local_lock.h \
  /src/include/linux/local_lock_internal.h \
  /src/include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  /src/include/linux/highuid.h \
  /src/include/linux/kobject_ns.h \
  /src/include/linux/stat.h \
  /src/arch/arm/include/uapi/asm/stat.h \
  /src/include/uapi/linux/stat.h \
  /src/include/linux/kref.h \
  /src/include/linux/refcount.h \
  /src/include/linux/kdev_t.h \
  /src/include/uapi/linux/kdev_t.h \
  /src/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/energy/model.h) \
    $(wildcard include/config/generic/msi/irq/domain.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/generic/msi/irq.h) \
    $(wildcard include/config/dma/ops.h) \
    $(wildcard include/config/dma/declare/coherent.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/arch/has/sync/dma/for/device.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu/all.h) \
    $(wildcard include/config/dma/ops/bypass.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /src/include/linux/dev_printk.h \
  /src/include/linux/ratelimit.h \
  /src/include/linux/sched.h \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/sched/info.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/uclamp/task.h) \
    $(wildcard include/config/uclamp/buckets/count.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/psi.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/stackprotector.h) \
    $(wildcard include/config/arch/has/scaled/cputime.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/posix/cputimers.h) \
    $(wildcard include/config/posix/cpu/timers/task/work.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/io/uring.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/ubsan.h) \
    $(wildcard include/config/ubsan/trap.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/x86/cpu/resctrl.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/rseq.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/kunit.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/vmap/stack.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/gcc/plugin/stackleak.h) \
    $(wildcard include/config/x86/mce.h) \
    $(wildcard include/config/arch/task/struct/on/stack.h) \
    $(wildcard include/config/debug/rseq.h) \
  /src/include/uapi/linux/sched.h \
  /src/include/linux/pid.h \
  /src/include/linux/rculist.h \
    $(wildcard include/config/prove/rcu/list.h) \
  /src/include/linux/sem.h \
  /src/include/uapi/linux/sem.h \
  /src/include/linux/ipc.h \
  /src/include/linux/rhashtable-types.h \
  /src/include/uapi/linux/ipc.h \
  arch/arm/include/generated/uapi/asm/ipcbuf.h \
  /src/include/uapi/asm-generic/ipcbuf.h \
  arch/arm/include/generated/uapi/asm/sembuf.h \
  /src/include/uapi/asm-generic/sembuf.h \
  /src/include/linux/shm.h \
  /src/include/uapi/linux/shm.h \
  /src/include/uapi/asm-generic/hugetlb_encode.h \
  arch/arm/include/generated/uapi/asm/shmbuf.h \
  /src/include/uapi/asm-generic/shmbuf.h \
  /src/arch/arm/include/asm/shmparam.h \
  /src/include/linux/kcov.h \
  /src/include/uapi/linux/kcov.h \
  /src/include/linux/plist.h \
    $(wildcard include/config/debug/plist.h) \
  /src/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/time/low/res.h) \
    $(wildcard include/config/timerfd.h) \
  /src/include/linux/hrtimer_defs.h \
  /src/include/linux/timerqueue.h \
  /src/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
    $(wildcard include/config/checkpoint/restore.h) \
  /src/include/uapi/linux/seccomp.h \
  arch/arm/include/generated/asm/seccomp.h \
  /src/include/asm-generic/seccomp.h \
  /src/include/uapi/linux/unistd.h \
  /src/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /src/arch/arm/include/uapi/asm/unistd.h \
  arch/arm/include/generated/uapi/asm/unistd-eabi.h \
  arch/arm/include/generated/uapi/asm/unistd-common.h \
  arch/arm/include/generated/asm/unistd-nr.h \
  /src/include/linux/resource.h \
  /src/include/uapi/linux/resource.h \
  arch/arm/include/generated/uapi/asm/resource.h \
  /src/include/asm-generic/resource.h \
  /src/include/uapi/asm-generic/resource.h \
  /src/include/linux/latencytop.h \
  /src/include/linux/sched/prio.h \
  /src/include/linux/sched/types.h \
  /src/include/linux/signal_types.h \
    $(wildcard include/config/old/sigaction.h) \
  /src/include/uapi/linux/signal.h \
  /src/arch/arm/include/asm/signal.h \
  /src/arch/arm/include/uapi/asm/signal.h \
  /src/include/uapi/asm-generic/signal-defs.h \
  /src/arch/arm/include/uapi/asm/sigcontext.h \
  arch/arm/include/generated/uapi/asm/siginfo.h \
  /src/include/uapi/asm-generic/siginfo.h \
  /src/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /src/include/linux/posix-timers.h \
  /src/include/linux/alarmtimer.h \
    $(wildcard include/config/rtc/class.h) \
  /src/include/linux/task_work.h \
  /src/include/uapi/linux/rseq.h \
  /src/include/linux/kcsan.h \
  /src/include/linux/energy_model.h \
  /src/include/linux/sched/cpufreq.h \
    $(wildcard include/config/cpu/freq.h) \
  /src/include/linux/sched/topology.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/sched/mc.h) \
  /src/include/linux/sched/idle.h \
  /src/include/linux/sched/sd_flags.h \
  /src/include/linux/ioport.h \
    $(wildcard include/config/io/strict/devmem.h) \
  /src/include/linux/klist.h \
  /src/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /src/include/linux/overflow.h \
  /src/include/linux/device/bus.h \
    $(wildcard include/config/acpi.h) \
  /src/include/linux/device/class.h \
  /src/include/linux/device/driver.h \
  /src/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/arm/dma/use/iommu.h) \
    $(wildcard include/config/arch/omap.h) \
  /src/include/linux/pm_wakeup.h \
  /src/include/linux/fs.h \
    $(wildcard include/config/read/only/thp/for/fs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/cgroup/writeback.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/fs/encryption.h) \
    $(wildcard include/config/fs/verity.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/unicode.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fs/dax.h) \
    $(wildcard include/config/mandatory/file/locking.h) \
    $(wildcard include/config/migration.h) \
  /src/include/linux/wait_bit.h \
  /src/include/linux/dcache.h \
  /src/include/linux/rculist_bl.h \
  /src/include/linux/list_bl.h \
  /src/include/linux/bit_spinlock.h \
  /src/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /src/include/linux/stringhash.h \
    $(wildcard include/config/dcache/word/access.h) \
  /src/include/linux/hash.h \
    $(wildcard include/config/have/arch/hash.h) \
  /src/include/linux/path.h \
  /src/include/linux/list_lru.h \
    $(wildcard include/config/memcg/kmem.h) \
  /src/include/linux/shrinker.h \
  /src/include/linux/capability.h \
  /src/include/uapi/linux/capability.h \
  /src/include/linux/semaphore.h \
  /src/include/linux/fcntl.h \
    $(wildcard include/config/arch/32bit/off/t.h) \
  /src/include/uapi/linux/fcntl.h \
  /src/arch/arm/include/uapi/asm/fcntl.h \
  /src/include/uapi/asm-generic/fcntl.h \
  /src/include/uapi/linux/openat2.h \
  /src/include/linux/migrate_mode.h \
  /src/include/linux/percpu-rwsem.h \
  /src/include/linux/rcuwait.h \
  /src/include/linux/sched/signal.h \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/stack/growsup.h) \
  /src/include/linux/signal.h \
    $(wildcard include/config/proc/fs.h) \
  /src/include/linux/sched/jobctl.h \
  /src/include/linux/sched/task.h \
    $(wildcard include/config/have/exit/thread.h) \
    $(wildcard include/config/arch/wants/dynamic/task/struct.h) \
    $(wildcard include/config/have/arch/thread/struct/whitelist.h) \
  /src/include/linux/uaccess.h \
    $(wildcard include/config/set/fs.h) \
  /src/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/fault/injection/usercopy.h) \
  /src/include/linux/instrumented.h \
  /src/arch/arm/include/asm/uaccess.h \
    $(wildcard include/config/cpu/sw/domain/pan.h) \
    $(wildcard include/config/cpu/use/domains.h) \
    $(wildcard include/config/uaccess/with/memcpy.h) \
  /src/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/cp15/mmu.h) \
  arch/arm/include/generated/asm/extable.h \
  /src/include/asm-generic/extable.h \
  /src/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  /src/include/linux/key.h \
    $(wildcard include/config/key/notifications.h) \
    $(wildcard include/config/net.h) \
    $(wildcard include/config/sysctl.h) \
  /src/include/linux/sysctl.h \
  /src/include/uapi/linux/sysctl.h \
  /src/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /src/include/linux/sched/user.h \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/bpf/syscall.h) \
    $(wildcard include/config/watch/queue.h) \
  /src/include/linux/rcu_sync.h \
  /src/include/linux/delayed_call.h \
  /src/include/linux/uuid.h \
  /src/include/uapi/linux/uuid.h \
  /src/include/linux/errseq.h \
  /src/include/linux/ioprio.h \
  /src/include/linux/sched/rt.h \
  /src/include/linux/iocontext.h \
  /src/include/linux/fs_types.h \
  /src/include/uapi/linux/fs.h \
  /src/include/uapi/linux/ioctl.h \
  arch/arm/include/generated/uapi/asm/ioctl.h \
  /src/include/asm-generic/ioctl.h \
  /src/include/uapi/asm-generic/ioctl.h \
  /src/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /src/include/linux/percpu_counter.h \
  /src/include/uapi/linux/dqblk_xfs.h \
  /src/include/linux/dqblk_v1.h \
  /src/include/linux/dqblk_v2.h \
  /src/include/linux/dqblk_qtree.h \
  /src/include/linux/projid.h \
  /src/include/uapi/linux/quota.h \
  /src/include/linux/nfs_fs_i.h \
  /src/include/linux/slab.h \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/have/hardened/usercopy/allocator.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
  /src/include/linux/percpu-refcount.h \
  /src/include/linux/kasan.h \
    $(wildcard include/config/kasan/vmalloc.h) \
    $(wildcard include/config/kasan/generic.h) \
    $(wildcard include/config/kasan/inline.h) \
  /src/include/linux/module.h \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/have/static/call/inline.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/function/error/injection.h) \
  /src/include/linux/kmod.h \
  /src/include/linux/umh.h \
  /src/include/linux/elf.h \
    $(wildcard include/config/arch/use/gnu/property.h) \
    $(wildcard include/config/arch/have/elf/prot.h) \
  /src/arch/arm/include/asm/elf.h \
  /src/arch/arm/include/asm/vdso_datapage.h \
  /src/include/vdso/datapage.h \
    $(wildcard include/config/arch/has/vdso/data.h) \
  /src/include/uapi/asm-generic/errno-base.h \
  /src/include/vdso/clocksource.h \
    $(wildcard include/config/generic/gettimeofday.h) \
  /src/arch/arm/include/asm/vdso/clocksource.h \
  /src/include/vdso/processor.h \
  /src/arch/arm/include/asm/vdso/gettimeofday.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /src/arch/arm/include/asm/vdso/cp15.h \
    $(wildcard include/config/cpu/cp15.h) \
  /src/arch/arm/include/asm/user.h \
  /src/include/uapi/linux/elf.h \
  /src/include/uapi/linux/elf-em.h \
  /src/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /src/include/linux/rbtree_latch.h \
  /src/include/linux/error-injection.h \
  /src/include/asm-generic/error-injection.h \
  /src/include/linux/tracepoint-defs.h \
  /src/include/linux/static_key.h \
  /src/include/linux/static_call_types.h \
    $(wildcard include/config/have/static/call.h) \
  /src/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
    $(wildcard include/config/arm/module/plts.h) \
  /src/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /project/kamv_linked_list.h \

/project/kamv_linked_list.o: $(deps_/project/kamv_linked_list.o)

$(deps_/project/kamv_linked_list.o):

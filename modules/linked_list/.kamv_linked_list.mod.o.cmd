cmd_/project/kamv_linked_list.mod.o := arm-linux-gnueabihf-gcc -Wp,-MMD,/project/.kamv_linked_list.mod.o.d  -nostdinc -isystem /usr/lib/gcc-cross/arm-linux-gnueabihf/8/include -I/src/arch/arm/include -I./arch/arm/include/generated -I/src/include -I./include -I/src/arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I/src/include/uapi -I./include/generated/uapi -include /src/include/linux/kconfig.h -include /src/include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -fmacro-prefix-map=/src/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-ipa-sra -msoft-float -mabi=aapcs-linux -mfpu=vfp -funwind-tables -marm -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-a -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -O2 --param=allow-store-data-races=0 -Wframe-larger-than=1024 -fstack-protector-strong -Wimplicit-fallthrough -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned  -DMODULE  -DKBUILD_BASENAME='"kamv_linked_list.mod"' -DKBUILD_MODNAME='"kamv_linked_list"' -c -o /project/kamv_linked_list.mod.o /project/kamv_linked_list.mod.c

source_/project/kamv_linked_list.mod.o := /project/kamv_linked_list.mod.c

deps_/project/kamv_linked_list.mod.o := \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/retpoline.h) \
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
    $(wildcard include/config/arch/use/builtin/bswap.h) \
    $(wildcard include/config/kcov.h) \
  /src/include/linux/module.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tree/srcu.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/jump/label.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/have/static/call/inline.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/function/error/injection.h) \
  /src/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
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
    $(wildcard include/config/panic/timeout.h) \
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
    $(wildcard include/config/trim/unused/ksyms.h) \
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
  /src/include/linux/jump_label.h \
    $(wildcard include/config/have/arch/jump/label/relative.h) \
  /src/arch/arm/include/asm/jump_label.h \
  /src/arch/arm/include/asm/div64.h \
  /src/arch/arm/include/asm/compiler.h \
  /src/include/asm-generic/div64.h \
  /src/include/linux/stat.h \
  /src/arch/arm/include/uapi/asm/stat.h \
  /src/include/uapi/linux/stat.h \
  /src/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
    $(wildcard include/config/posix/timers.h) \
  /src/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  /src/include/vdso/math64.h \
  /src/include/linux/time64.h \
  /src/include/vdso/time64.h \
  /src/include/uapi/linux/time.h \
  /src/include/uapi/linux/time_types.h \
  /src/include/linux/time32.h \
  /src/include/linux/timex.h \
  /src/include/uapi/linux/timex.h \
  /src/arch/arm/include/asm/timex.h \
  /src/include/vdso/time32.h \
  /src/include/vdso/time.h \
  /src/include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  /src/include/linux/highuid.h \
  /src/include/linux/kmod.h \
  /src/include/linux/umh.h \
  /src/include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/contig/alloc.h) \
    $(wildcard include/config/cma.h) \
  /src/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  /src/include/linux/bug.h \
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
  /src/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/shadow/call/stack.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/holes/in/zone.h) \
  /src/include/linux/spinlock.h \
    $(wildcard include/config/preemption.h) \
  /src/include/linux/preempt.h \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/trace/preempt/toggle.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/arm/include/generated/asm/preempt.h \
  /src/include/asm-generic/preempt.h \
  /src/include/linux/thread_info.h \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  /src/include/linux/restart_block.h \
  /src/include/linux/errno.h \
  /src/include/uapi/linux/errno.h \
  arch/arm/include/generated/uapi/asm/errno.h \
  /src/include/uapi/asm-generic/errno.h \
  /src/include/uapi/asm-generic/errno-base.h \
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
  /src/arch/arm/include/asm/glue.h \
  /src/arch/arm/include/asm/pgtable-2level-types.h \
  /src/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/xip/kernel.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/xip/phys/addr.h) \
  /src/include/linux/sizes.h \
  /src/include/asm-generic/memory_model.h \
  /src/include/linux/pfn.h \
  /src/include/asm-generic/getorder.h \
  /src/include/linux/bottom_half.h \
  /src/include/linux/lockdep.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
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
  /src/arch/arm/include/asm/smp.h \
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
  /src/include/linux/wait.h \
  arch/arm/include/generated/asm/current.h \
  /src/include/asm-generic/current.h \
  /src/include/uapi/linux/wait.h \
  /src/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
    $(wildcard include/config/numa/keep/meminfo.h) \
  /src/include/linux/seqlock.h \
  /src/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/debug/mutexes.h) \
  /src/include/linux/osq_lock.h \
  /src/include/linux/debug_locks.h \
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
  /src/include/linux/rcutree.h \
  /src/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/debug/rwsems.h) \
  /src/include/linux/err.h \
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
  /src/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  /src/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
    $(wildcard include/config/bl/switcher.h) \
  /src/include/asm-generic/topology.h \
  /src/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /src/include/uapi/linux/sysctl.h \
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
  /src/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /src/arch/arm/include/uapi/asm/unistd.h \
  arch/arm/include/generated/uapi/asm/unistd-eabi.h \
  arch/arm/include/generated/uapi/asm/unistd-common.h \
  arch/arm/include/generated/asm/unistd-nr.h \
  /src/arch/arm/include/asm/vdso/cp15.h \
    $(wildcard include/config/cpu/cp15.h) \
  /src/arch/arm/include/asm/user.h \
  /src/include/uapi/linux/elf.h \
  /src/include/uapi/linux/elf-em.h \
  /src/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /src/include/linux/sysfs.h \
  /src/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /src/include/linux/idr.h \
  /src/include/linux/radix-tree.h \
  /src/include/linux/xarray.h \
    $(wildcard include/config/xarray/multi.h) \
  /src/include/linux/kconfig.h \
  /src/include/linux/local_lock.h \
  /src/include/linux/local_lock_internal.h \
  /src/include/linux/kobject_ns.h \
  /src/include/linux/kref.h \
  /src/include/linux/refcount.h \
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
  /src/include/linux/build-salt.h \
    $(wildcard include/config/build/salt.h) \
  /src/include/linux/elfnote.h \
  /src/include/linux/vermagic.h \
  include/generated/utsrelease.h \
  /src/arch/arm/include/asm/vermagic.h \

/project/kamv_linked_list.mod.o: $(deps_/project/kamv_linked_list.mod.o)

$(deps_/project/kamv_linked_list.mod.o):

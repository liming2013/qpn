/**
@page history Revision History

@section qpn_5_5_1 Version 5.5.1, 2015-10-06

This release adds state machine operations for implementing the shallow history mechanism. The operations are called QMsm_childStateObj() and QHsm_childState(), for QMsm and QHsm classes, respectively, because they compute a child state of a given parent, such that the child belongs to the same state hierarchy as the current state.

This release also improves the AAPCS compliance of the ARM Cortex-M port to the QK preemptive kernel. Specifically, the PendSV handler in assembly did not always maintain the 8-byte stack alignment, which is required by AAPCS. This version corrects the stack misalignment in the qk_port.s files for all supported ARM compilers (ARM-Keil, GNU, IAR, and TI CCS). All these ports should also be ready for ARM Cortex-M7.

Also, this release adds support for the TI CCS ARM compiler. Specifically, a new ARM Cortex-M ports have been added (in directories `qpn\ports\arm-cm\qk\ti\` and `qpn\ports\arm-cm\qk\ti\`) and TI CCS example projects have been provided (in directories `qpn\examples\arm-cm\dpp_ek-tm4c123gxl\qk\ti\` and `qpn\examples\arm-cm\dpp_ek-tm4c123gxl\qv\ti\`).


Changes in detail:

1. Added the new prototypes QMsm_childStateObj() and QHsm_childState() to qepn.h

2. Added implementation of QMsm_childStateObj() and QHsm_childState() to qepn.c

3. Modified the qk_port.s assembly implementation for all supported ARM Cortex-M toolsets (ARM-Keil, GNU, IAR, and TI CCS)

4. Added QP-nano Cortex-M port to TI CCS.

5. Added CCS example projects in `qpn\ports\arm-cm\qk\ti\` and `qpn\ports\arm-cm\qk\ti\


------------------------------------------------------------------------------
@section qpn_5_4_2 Version 5.4.2, 2015-06-07

The main focus of this release is to improve the support for "dual targeting" of QP-nano applications, which is developing of deeply embedded code as much as possible on the desktop OS, such as Windows. Experience shows that "dual targeting" dramatically improves productivity of embedded systems developers, perhaps more than any other technique.

This release makes it possible to use exactly the **same** application code, main function, and the Board Support Package interface (bsp.h) on both deeply embedded target and on Windows. The only differences between these targets can be completely encapsulated in the Board Support Package implementation (bsp.c).

The support for "dual targeting" in this QP-nano release works both for Win32 console and Win32 GUI applications. The Win32-GUI support enables developers to easily emulate the front-panels of the embedded devices, with LCD-screens (graphical and segmented), LEDs, buttons, switches, sliders, etc.

Changes in detail:

1. Modified the QP-nano port to Windows (@ref win32-qv) so that it supports both Win32 console and Win32-GUI applications. The newly introduced pre-processor #WIN32_GUI macro is now required to use the Win32-GUI facilities.

2. Added portable "safe" macros from `<stdio.h>` and `<string.h>` to the QP-nano port to Windows. These macros encapsulate the differences between Microsoft Visual C++ and other compilers (such as MinGW).

3. Simplified the structure of the QP-nano Windows port by eliminating one level of directories for the compilers used. Both VC++ and MinGW builds can now be run in the same port directory.

4. Modified the QF_stop() function in the QP-nano port to @ref win32-qv, so that it unblocks the QV event-loop and thus lets the application terminate. 

5. Modified all examples for Windows to use the new port structure.

6. Improved all Makefiles (for the MinGW toolset) in all Windows examples, to make them easier to adapt to custom applications, both Win32 console and Win32 GUI.

7. Moved several examples from the `examples/win32/` and examples/win32-qv directories to `examples/arm-cm/` directory with native embedded examples for ARM Cortex-M. This co-location of the Win32 emulation with the embedded code running on the actual board demonstrates better the "dual targeting" development approach.

8. Made the ::QActiveCB (::QActive Control Block) to the QP-nano backwards-compatibility layer as deprecated. Instead, the newer QP-nano applications should use ::QMActiveCB. 

9. Updated all Windows examples to the latest QP API by compiling the code with the macro #QP_API_VERSION set to 9999 (latest API without backwards compatibility)


------------------------------------------------------------------------------
@section qpn_5_4_0 Version 5.4.0, 2015-05-31

This release changes the basic philosophy of packaging and distributing the QP-nano framework by **combining** the "QP-nano Baseline Code" with all currently available "QP-nano Development Kits" (QDK-nano). This is done to eliminate any potential mistakes in downloading and installing separate pieces of code.

This release also changes the active object class hierarchy so that ::QMActive is now more fundamental and is the base class for ::QActive. (Previously ::QMActive was a subclass of ::QActive). The newly added documentation section about @ref classes "QP-nano Design" shows the current class hierarchy.

@note
Because the types ::QMActive and ::QActive are equivalent in QP-nano, this change has minimal impact on the applications, but it is now more correct to use ::QMActive as the base class for all "opaque" active object pointers.

Additionally, this release alignes the QP-nano framework better with the rest of the QP framework family (QP/C and QP/C++), so that fewer changes are needed to move applications between QP-nano and QP/C. 

Finally, this release adds periodic time events (timers) to QP-nano. The feature is demonstrated by many provided examples (e.g., "Blinky", "Fly 'n' Shoot" game, PELICAN crossing).


The aforementioned changes have also the following ripple effects:

1. The structure of the QP-nano ports has been modified to match QP/C and to avoid repetitions. The QP-nano application no longer need to provide and #include the complete port `qpn_port.h` header file, which is now deprecated. Insted QP-nano application code needs to #include the <span class="img file_h">qpn.h</span> (QP-nano API) header file, which also now contains the QP-nano backwards-compatibility layer.

2. The application is now only responsible for providing the <span class="img file_h"><a href="qpn__conf_8h.html"><strong>qpn_conf.h</strong></a></span> file to set up the basic configuration for QP-nano. Examples of the `qpn_config.h` configurations are provided in all supplied QP-nano examples.

3. The actual port (e.g., the interrupt disabling policy for tasks and interrupts, interrupt entry/exit code, etc.) is included from the <span class="img folder">@ref ports</span> folder. This <span class="img folder">@ref ports</span> folder has been reorganized to contain all currently available QP-nano ports. The ports are organized into two categories: @ref ports_native "native QP-nano ports" ("bare-metal") and @ref ports_os "ports to big operating systems" (Windows and Linux).(**NOTE**: the ports are now documented in the this <strong>QP-nano Reference Manual</strong>. Each port sub-directory contains a <span class="img qp_link">README</span> link to the corresponding page in the online documentation)

4. Expanded the QP-nano time events (timers) with the ability to fire periodically. The feature is controlled by the preprocessor switch #QF_TIMEEVT_PERIODIC. When this macro is defined (in the `qpn_config.h` header file), the signature of the QActive_armX() function contains one more `interval` parameter. The `interval` parameter allows you to specify the interval of the periodic timeout. If the `interval` is zero, the time event is one-shot.
    
5. It is no longer necessary to define the **QPN environment variable** to build the QP-nano examples. All directories and files referenced by example projects are **relative** to the project folder. This change reflects the fact that most development tools add source files to the project using relative paths.   

6. The QP-nano <span class="img folder">@ref exa</span> folder has been reorganized to reduce the repetitions and contains all currently available QP-nano examples. The folder includes four categories of examples: @ref exa_native "native QP-nano examples" ("bare-metal") and @ref exa_os "examples for big operating systems" (Windows and Linux). The <span class="img folder">examples</span> folder has been expanded to contain all currently available QP-nano examples, many of them are new in this release. (**NOTE**: the currently available examples are now documented in the <strong>QP-nano Reference Manual</strong>. Each example sub-directory contains a <span class="img qp_link">README</span> link to the corresponding page in the online documentation)

7. A new <span class="img folder">3rd_party</span> folder created to contain the Third-Party code used in the QP-nano ports and examples, such as MCU register files, low-level startup code, device drivers, etc. The <span class="img folder">3rd_party</span> folder avoids the need to repeat such code in every project. Also, the separation of the Third-Party components helps to clearly indicate code that comes from various sources, and to which Quantum Leaps, LLC expressly makes **no claims of ownership**. The Third-Party software components included in this "3rd_party" folder are licensed under a variety of different licensing terms that are defined by the respective owners of this software and are spelled out in the README.txt or LICENSE.txt files included in the respective sub-folders.

8. This release also comes with the much expanded online <strong>QP-nano Reference Manual</strong>, which is cross-linked with the ports and examples.


Changes in detail:

1. Renamed the "Vanilla" scheduler to the @ref comp_qv "QV-nano cooperative kernel" for symmetry with the @ref comp_qk "QK-nano preemptive kernel". Renamed QF_onIdle() callback to QV_onIdle().

2. Removed class ::QFsm (which is now deprecated). Legacy state machines coded in the "QFsm-style" will continue to work, but will use the ::QHsm implementation internally. There is no longer any efficiency advantage in using the "QFsm-style" state machines.

3. Updated @ref exa_arm-cm "ARM Cortex-M examples" and provided new examples for NXP mbed-LPC1768, and STM32 NUCLEO-L053R8, and NUCLEO-L152RE boards. All examples now use the latest CMSIS (V4.3.0). All ARM Cortex-M exampels are provided for the ARM-KEIL, GNU-ARM, and IAR-ARM toolsets.

4. Added the native @ref arm7-9 "port" and @ref exa_arm7-9 "examples" to the @ref arm7-9 "classic ARM7/9" with AT91SAM7S-EK board and the IAR-ARM toolset.

5. Added the native @ref avr "port" and @ref exa_avr "examples" to the AVR (AVRmega) with GNU-AVR and IAR-AVR toolsets. The @ref exa_avr "examples" are provided for the Arduino-UNO board. 

6. Added the native @ref msp430 "port" and @ref exa_msp430 "examples" to MSP430 with TI CCS-430 and IAR-430 toolsets. The @ref exa_msp430 "examples" are provided for the MSP430 LauchPad boards (the MSP-EXP430G2 and MSP-EXP430F5529LP for the "classic" MSP430 and "extened" MSP430X, respectively).

7. Updated @ref win32-qv "port to Win32-QV" (Windows with cooperative "Vanilla" scheduler, previously known as Win32-1T). Modified the port to apply a "fudge factor" in over-sizing QP-nano event queues and event pools, to minimize the risk of overflowing queues/pools due to non-deterministic Windows behavior.

8. Renamed the POSIX port to @ref posix-qv "POSIX-QV" (POSIX with cooperative "Vanilla" scheduler). Modified the port to apply a "fudge factor" in over-sizing QP-nano event queues and event pools, to minimize the risk of overflowing queues/pools due to non-deterministic behavior under POSIX.


------------------------------------------------------------------------------
@section qpn_5_3_0 Version 5.3.0, 2014-04-18

This release adds the "transition to history" (deep history) feature to
both QHsm and QMsm state machines and their subclasses. This QP-nano
release matches the new QM modeling tool Version 3.1.0, which now
supports the "transition to history" connector and the corresponding
code generation for transitions to history.

@note QP-nano 5.3.0 breaks backwards-compatibility with QP-nano
applications developed for QP-nano 4.x and 5.x. However, the update to
QP-nano 5.3.0 typically requires only to add #include <stdbool.h> and
#include "qassert.h" to the qpn_port.h header file in the application
directory. Any QM models created for the previous QP-nano versions
remain fully compatible with QP-nano 5.3.0, but you need to re-generate
the code with QM 3.1.0.

This release comes with new and updated QDKs for MSP430. Specifically,
new QDKs have been added for the MSP-EXP430G2 LaunchPad as well as the
MSP-EXP420F5529LP LauchPad. Also, the QDKs for MSP430 with the TI Code
Composer Studio are now part of the baseline QP-nano distribution.

This release also goes several steps towards compliance with the new
MISRA-C:2012 rules. For example, unused tag declarations have been
removed (MISRA-C:2012 Rule 2.4), the C99 standard Boolean data type in
<stdbool.h> has been added instead of uint8_t for stricter type
analysis, and the C99 data types uint_fast8_t and uint_fast16_t are used
instead of the non-standard uint_t.

Finally, this QP-nano release brings deep changes in the source code
comments and the doxygen documentation generated from the source code.
All comments have now more consistent structure, and every function is
now documented in the implementation file (.c file), whereas the
interface (.h files) contain only the brief descriptions of the
functions. This re-structuring of documentation is performed as part of
the validation and verification effort that has begun to provide a
certification package for QP-nano for safety standards, such as IEC
61508 and ISO 62304 (FDA 510(k)).


Changes in detail:

1. Moved detailed documentation of functions from the header files (.h)
to implementation files (.c).

2. Added macros: Q_TRAN_HIST(), QM_TRAN_HIST(), and QM_TRAN_EP(), to
"qepn.h"

3. Added attributes entryAction and initAction to the QMState struct in
"qepn.h" (needed for transition to history).

4. Changed return type to bool in virtual functions QMsmVtbl.post() and
QMsmVtbl.postISR() as well as the implementations: QActive_postX_(), and
QActive_postXISR_().

5. In qepn.h, changed the QState return type from action/state handler
functions to uint_fast8_t.

6. In qfn.h, changed the type of QActive attributes prio, head, tail,
and nUsed to uint_fast8_t.

7. In qfn.h, changed the type of of QTimeEvtCtr, as well of the tickRate
argument in QF_tickXISR(), QActive_armX(), and QActive_disarmX() to
uint_fast8_t.

8. Changed the return type from QK_schedPrio_() (priority) as well as
the p argument in QK_sched_() to uint_fast8_t

9. Added new QDKs-nano/IAR for MSP-EXP430G2 LaunchPad

10. Added new QDKs-nano/IAR for MSP-EXP420F5529LP LauchPad LaunchPad

11. Added new QDKs-nano/CCS for MSP-EXP430G2 LaunchPad

12. Added new QDKs-nano/CCS for MSP-EXP420F5529LP LauchPad LaunchPad


------------------------------------------------------------------------------
@section qpn_5_2_0 Version 5.2.0, 2013-12-30

This release matches the new QM 3.0.0, for which it provides model
examples based on the new QMsm/QMActive classes. This, in turn
demonstrates the new state machine code generation that QM3 was
specifically designed to do.

This release also provides consistent API for late-binding ("virtual"
functions) introduced in QP-nano 5.0.0, as opposed to using regular
linking (early-binding) for direct function calls, such as
QHsm_dispatch(). A clearly separated API compatibility layer is
provided, whereas you can configure a level of backwards compatibility
by means of the #QP_API_Version macro. This facilitates migrating
existing QP applications to the newer API.

An cyclomatic complexity (McCabe V(G)) analysis of this Version has been
performed and the maximum V(G) complexity per function has been reduced
to 15 by breaking up the QHsm_dispatch_() function. The code metrics
report, including cyclomatic complexity by function as well as other
standard code metrics (e.g., lines of code), is now included in the
"QP-nano Reference Manual", see
http://www.state-machine.com/qp/qpn/metrics.html

Finally, this release demonstrates safer stack allocation and safer
exception handlers in all ARM Cortex-M examples. The techniques are
described in the Embedded.com article "Are We Shooting Ourselves in the
Foot with Stack Overflow?".


Changes in detail:

1. In file qepn.h renamed the implementation functions, such as
QHsm_init() and QHsm_dispatch() to QHsm_init_() and QHsm_dispatch_()
(note the underscore, which means that the functions should not be
called directly by the application code). The only correct way of
calling the functions is through the macros QMSM_INIT() and
QMSM_DISPATCH(), respectively. The latter macros implement late-binding
("virtual" functions in C).

2. In file qfn.h renamed the implementation functions, such as
QActive_postX() and QActive_postXISR() to QActive_postX_(), and
QActive_postXISR_, respectively (note the underscore, which means that
the functions should not be called directly by the application code).
The only correct way of calling the functions is through the macros
QACTIVE_POST(), QACTIVE_POST_X(), QACTIVE_POST_ISR() and
QACTIVE_POST_X_ISR(). The latter macros implement late-binding
("virtual" functions in C).

3. for backwards compatibility, in files qepn.h and qfn.h defined "API
Compatibility Layer", which is controlled by the macro #QP_API_VERSION.
For example, specifying QP_API_VERSION=500 chooses API compatible with
QP Version 5.0.0 or newer, but excludes APIs that became deprecated in
the earlier versions. If the macro #QP_API_Version is not defined by the
user (typically on the command line for the compiler), the default value
of 0 is assumed. This default means maximum backwards compatibility
(from Version 0.0.0). On the other hand, higher values of
#QP_API_Version mean less backwards compatibility. For example
QP_API_VERSION=9999 will specify compatibility only with the latest
Version of QP-nano. The API Compatibility Layer for QP_API_Version < 500
provides macros: QHsm_init(), QHsm_dispatch(), QActive_post() and
QActive_postISR(). These macros resolve to QMSM_INIT() and QMSM_DISPATCH(),
QACTIVE_POST() and QACTIVE_POST_ISR() respectively, so that calls based
on the older API also use late-binging.

4. In file qepn.c, broken up the function QHsm_dispatch() into two
functions QHsm_dispatch_() and QHsm_tran_(). This has reduced the
cyclomatic complexity from 25 for the original function, to 11 and 15
for QHsm_dispatch_() and QHsm_tran_(), respectively.

5. Updated all examples for ARM Cortex-M to use safer stack allocation
and safer exception handlers in all ARM Cortex-M examples, as described
in the Embedded.com article "Are We Shooting Ourselves in the Foot with
Stack Overflow?".


------------------------------------------------------------------------------
@section qpn_5_1_1 Version 5.1.1, 2013-10-15

@note QP-nano 5.1.1 remains backwards-compatible with the existing
QP-nano 4.x applications, except QP-nano 5.1.x requires changing the
interrupt priority setting in the existing ARM Cortex-M applications.
Specifically, you need to set the interrupt priorities equal or lower
than <b>QF_AWARE_ISR_CMSIS_PRI</b> constant provided in the qfn_port.h
header file.

The main purpose of this milestone QP-nano release is to enable the QM
modeling tool to generate a new type of state machine code (requires QM
Version 3.0.0, which is still in development as of this writing).

This new type of state machine implementation in QP-nano 5 is based on
the new QMsm class, which takes advantage of the QM tool as an advanced
"state machine compiler". QM can perform optimizations that were not
possible with the C preprocessor alone. Specifically, the QM can easily
determine the LCA (Least-Common-Ancestor) state for every transition and
it can generate the complete transition-sequences (sequences of
exit/entry/initial actions) at code-generation time. The resulting code
can be still highly human-readable, but it will no longer be
human-maintainable. The lab tests indicate that the new "housekeeping"
code for executing hierarchical state machines can be about twice as
fast as the previous code based on the QHsm class. Additionally, the new
code requires less run-time support (smaller event processor) and uses
70% less of stack space in the call to the QMsm_dispatch() operation
than QHsm_dispatch().

The next big feature introduced in QP-nano 5 is polymorphism ("virtual"
functions) for basic operations, such as state machine init() and
dispatch() and active object post(), and postISR() operations. Making
theses functions "virtual" means that all these operations can be
re-defined in sub-classes of state machines and active objects. This, in
turn, allows a single application to use a mix of state machine classes
derived from the new QMsm base class with state machines derived from
the QHsm base class, each one using a different state machine
implementation strategy. Additionally, the virtual post() operation
could be very useful for implementing various Proxy active objects
(e.g., for active object event posting across networks).

Another big feature introduced in QP-nano 5 are the multiple,
independent system clock tick rates for time events. The number of
system tick rates can be now configured in the QP-nano ports. For
example, a digital watch can use a "fast" clock tick rate of 100Hz and a
"slow" clock tick rate of only 1Hz. These clock tick rates can be
managed independently, so for example, the fast clock tick rate can be
shut down in the absence of time events assigned to this rate. This
feature allows the applications to implement sophisticated power-saving
policies.

As yet another important feature, QP-nano adds a new "extended" API for
non-asserting event allocation and posting. This feature is intended for
situations, where an application is hammered with external events that
at times arrive too fast for processing, but that can be ignored under
the overload conditions. In those cases firing an assertion inside the
framework is undesirable. The non-asserting API allows a designer to
request a safety-margin when allocating or posting an event. The event
is not allocated/posted if the safety margin cannot be satisfied at the
time of the call. On the other hand, the safety margin allows the
application to still use the regular (asserting) event allocation and
posting, because the event pools and event queues are guaranteed to
maintain a minimal margin for safe operation.

Finally, QP-nano 5.1.0 never completely disables interrupts in the ARM
Cortex-M3/M4 cores, even inside the critical sections. On Cortex-M3/M4
(ARMv7-M architectures), the QP port disables interrupts selectively
using the BASEPRI register. (NOTE: The BASEPRI register is not
implemented in the ARMv6-M architecture (Cortex-M0/M0+), so
Cortex-M0/M0+ need to use the PRIMASK register to disable interrupts
globally).

This new policy of disabling interrupts divides interrupts into
"kernel-unaware" interrupts, which are never disabled, and
"kernel-aware" interrupts, which are disabled in the QP critical
sections. Only "kernel-aware" interrupts are allowed to call QP
services. "Kernel-unaware" interrupts are *NOT* allowed to call any QP
services and they can communicate with QP only by triggering a
"kernel-aware" interrupt (which can post or publish events).

As mentioned above, all QP ports to ARM Cortex-M included in the QP
5.1.x Baseline Code provide the constant QF_AWARE_ISR_CMSIS_PRI, which
must be used to offset the "kernel-aware" interrupt priorities.

All example projects for ARM Cortex-M included in the QP-nano 5.1.x
Baseline Code demonstrate the recommended way of assigning interrupt
priorities in your applications. The initialization consist of two steps:

1. you enumerate the "kernel-unaware" and "kernel-aware" interrupt
priorities (whereas you offset the "kernel-aware" priorities by the
constant QF_AWARE_ISR_CMSIS_PRI) and

2. you assign the priorities to *ALL* interrupts by calling the
NVIC_SetPriority() CMSIS function.

****
NOTE: Leaving the interrupt priority at the default value of zero
(the highest priority) is most likely incorrect, because the
"kernel-unaware" interrupts cannot call any QP services.
****

For more information, please read the short Application Note "Setting
ARM Cortex-M Interrupt Priorities in QP 5.1" available at:
http://www.state-machine.com/arm/AN_ARM-Cortex-M_Interrupt-Priorities.pdf.

The following list details the changes:

1. Added the new QMsm "class" to qepn.h. Changed the inheritance tree by
deriving QHsm and QFsm from the QMsm base class. Added virtual table
structures for QMsm, QHsm, and QFsm (polymorphism).
    - added macro QMSM_INIT() to polymorphically call the state
      machine initialization implementation in the QMsm base class and
      all subclasses.
    - added macro QMSM_DISPATCH() to polymorphically call the state
      machine event dispatching implementation  in the QMsm base class
      and all subclasses.

2. Added the new "QMActive" "class" to qfn.h. Extended the inheritance
tree to derive QMActive from QActive. Added virtual table structures for
QMActive and QActvie (polymorphism).
    - added macro QACTIVE_POST() to polymorphically call the direct
      event posting to an active object.
    - added macro QACTIVE_POST_ISR() to polymorphically call the
      postISR (posting from interrupts) to an active object.

3. Added the multiple system clock tick rates feature in qfn.h:
    - added new configuration macro QF_MAX_TICK_RATE, which specifies
      the number of clock tick rates. This macro is to be defined in
      the QF ports (in the qpn_port.h header file). If the macro is
      undefined, the default value is 1 (one clock tick rate).
    - renamed and re-implemented the QF_tickISR() function as the
      "extended" QF_tickXISR() function with the argument 'tickRate' for
      processing time events allocated to different clock rates. The
      application must call QF_tickXISR(0), QF_tickXISR(1), ... at the
      specified tick rates from ISRs or *tasks*.
    - renamed and re-implemented the internal function QTimeEvt_arm_()
      to a public function QActive_armX() for arming time events
      initialized with the "extended" constructor. The QActive_armX()
      function is the new recommended API for arming time events, both
      one-shot and periodic.
    - re-implemented QActive_disarm().
    - extended QF_timerSetX_ to an array of [QF_MAX_TICK_RATE], so that
      every rate can be checked independently.

4. Added the new non-asserting API to qf.h:
    - added functions QActive_postX() and QActive_postXISR() to post an
      event to the given active object. The functions do not post the
      event if the target event queue has less free slots than the
      specified margin. The functions assert if the margin is zero and
      the event can't be posted.

5. Changed the structure of the ARM Cortex-M ports
    - renamed the sub-directory for ARM Cortex-M ports and examples
      from "arm-cortex" to "arm-cm". This is done to avoid confusion
      with other ARM Cortex variants, such as Cortex-A/R, which very
      different from Cortex-M.
    - removed the CMSIS (Cortex Microcontroller Software Interface
      Standard) directories from the Cortex-M examples and moved it to
      the common location in the %QPN%/ports/arm-cm/cmsis/ directory.
      Upgraded the CMSIS to the latest Version 3.20.
    - added the ARM Cortex-M ports and examples with Keil/ARM MDK to
      the QP Baseline Code.
    - upgraded ARM Cortex-M ports with IAR to the latest IAR EWARM 6.60
    - upgraded ARM Cortex-M ports with Sourcery CodeBench to the latest
      Version 2013.05-53.

9. Added the requested simple "Blinky" example for Windows and ARM
Cortex-M (with the GNU, IAR, and Keil toolsets).
    - Added "Getting Started with QP-nano" guide based on the Blinky
      example.

10. Modified the application examples with PC-Lint
(qpn/examples/arm-cm/gnu/dpp-qk_ek-lm3s811-lint and
qpn/examples/arm-cm/iar/dpp-qk_ek-lm3s811-lint). Updated lint files for
the latest PC-Lint

11. Ported all state pattern examples to Win32/MinGW. That way, all
these examples can be run and modified directly on Windows, without
going back to DOS.

12. Updated the Doxygen documentation (QP-nano Reference Manual)
    - updated the QP-nano tutorial
    - updated and added documentation and code samples
    - added search box and tree-view panel to the HTML documentation


------------------------------------------------------------------------------
@section qpn_4_5_04 Version 4.5.04, 2013-02-09

The main purpose of this release is adding support for the ARM Cortex-M4F
processors with the hardware Floating-Point Unit (FPU). The QP-nano ports
to Cortex-M4F take full advantage of the "lazy stacking" feature of the
FPU registers, and by doing so offer the most efficient preemptive
multitasking on this processor.

Changes in detail:

1. Added ports and examples for ARM Cortex-M4F with the EK-LM4F120XL
board (Stellaris Launchpad).

2. Added the macro QF_LOG2(), which can be re-implemented in the QP-nano
ports, if the CPU supports special instructions, such as CLZ (count leading
zeros in Cortex-M3/M4). If the macro is not defined in the QP port, the
default implementation uses a lookup table.

3. Updated all ARM Cortex-M ports and examples to the latest IAR EWARM
6.50 and Sourcery CodeBench 2012.09-85.

4. Updated App Notes "QP and ARM Cortex-M with IAR" and "QP and ARM
Cortex-M with GNU".

5. Updated the PC-Lint support files (include/lib-qpn.lnt, au-misra2.lnt)
to the latest PC-Lint 9.00j.

6. Updated the Application Note: "QP-nano MISRA-C:2004 Compliance Matrix".

7. Spell-checked the comments in all QP-nano source files and removed
several typos.

8. Removed the Qt ports and examples from the QP-nano Baseline Code and

@note QP-nano Version 4.5.04 preserves full compatibility with QM 2.2.03
and all existing QDKs for QP-nano 4.5.xx.


------------------------------------------------------------------------------
@section qpn_4_5_03 Version 4.5.03, 2012-11-29

This release changes the directory structure of QP-nano examples
for  various operating systems, such as POSIX (Linux, BSD, etc.),
Win32 (Windows), Qt, etc. The OS examples are moved from the
exampels/80x86/ directory one level up to examples/.


------------------------------------------------------------------------------
@section qpn_4_5_02 Version 4.5.02, 2012-08-17

The main purpose of this release is providing QM models in most
examples and better, more comprehensive support for (rapid)
prototyping of embedded QP applications on the desktop with the
Win32 API and with Qt. Among others, this release adds a complete
toolkit for creating realistic embedded front panels with pure
Win32-GUI API and free Visual C++ Express and ResEdit. An extensive
Application Note "QP and Win32" is included in this release.

This QP relase adds QM models, created with the new QM 2.2.01,
to most of the examples. The code generated by this new QM version
complies with MISRA-C:2004 rules.

This release adds the variable QF_timerSet_ and bookkeeping
around it, so that the state of all timeouts in the system can
be determined quickly and efficiently. This feature is for power-
sensitive applications, where the system clock tick interrupt
needs to be turned off. One of the criteria to entering such a
sleep mode is that all timeout events are disarmed, that is,
when (QF_timerSet_ == (uint8_t)0).

Changes in detail:

1. Added QF_timerSet_ declaration to qfn.h and setting/clearing
this bitmask into qfn.c and qfn_init.c. This feature is controled
by the configuration macro Q_TIMERSET.

2. Modified QP-nano port to Win32 and used the free Visual C++ Express
2010 with Platform SDK rather than Visual C++ Pro 2008. Provided a
completely revised App Note "QP and Win32".

3. Renamed the port directory qt_1t/ to qt/.

4. Added QM models to most examples and used the automatically
generated code from the models instead of the hand-written code.

5. Added .ui files to the Qt examples for generating UIs
graphically with the Qt Designer tool. Revised and updated the
App Note "QP and Qt".

6. Removed definition of the macro QF_FSM_ACTIVE from qpn_port.h
files in <qpn>/examples/80x86/watcom/dpp and
<qpn>/examples/80x86/watcom/game. This configuration conflicted
with the actual definition of the active objects, which used
*hierarchical* state machines, not the "flat" state machines.


------------------------------------------------------------------------------
@section qpn_4_5_01 Version 4.5.01, 2012-06-14

The main purpose of this minor release is providing improved
MISRA-compliant state machine implementation. Specifically, a new
macro Q_UNHANDLED() has been added for a situation when a guard
condition evaluates to FALSE, but the state model does not prescribe
the explicit [else] case for this guard. In this case, the state
handler can return Q_UNHANDLED(), which will cause the QEP event
processor to propagate the event to the superstate, which is what
UML semantics prescribes.

NOTE: These change to the QEP-nano event processor is completely
backwards-compatible. All state hander functions coded the old
way will continue to handle the guard conditions correctly and
in accordance with the UML specification. The new Q_UNHANDLED()
macro is necessary only for MISRA-compliant state handler coding,
which will be applied in the upcoming release of the QM modeling
and code generation tool.  

Changes in detail:

1. Added macro Q_UNHANDLED() and return value Q_RET_UNHANDLED in
qepn.h.

2. Modified qepn.c to handle the Q_RET_UNHANDLED return value.

3. Updated the QP-nano MISRA-C:2004 compliance matrix to 
include the new MISRA-compliant way of coding guard conditions.

4. Updated the IAR ARM compiler used in the ARM Cortex-M examples
to the latest Version IAR EWARM 6.40.

5. Modified the Qt port not to define the QPApp::onClockTick()
slot, but instead to allow defining this slot in the BSP of the
application.


------------------------------------------------------------------------------
@section qpn_4_5_00 Version 4.5.00, 2012-05-30

The main pupose of this relase is to improve host-based development of
QP-nano applications, which is critical for Test-Driven Development (TDD).
Among others, this release provides integration between QP-nano and the
popular Qt GUI framework, which allows developers to easily build host-
based simulations of the embedded systems with the realistic user
interfaces.

This realase also simplifies implementing transitions to history, which
is a preparation to providing this feature in the QM modeling tool.

Changes in detail:

1. Renamed the event class from QEvent to QEvt to avoid a name conflict
with the Qt framework.

NOTE: To minimize impact of this change on the existing QP-nano ports
and applications, the name QEvent is provided as well, but this can be
suppressed by defining the configuration macro Q_NQEVENT in qep_port.h.

2. Added return value to QF_run() to allow transfer of the exit
status to the destop operating systems.

NOTE: This modification haves impact on most QP-nano ports, because
the QF_run() function must now return a int16_t value.

3. Added member 'temp' to the QHsm and QFsm base classes to prevent
clobbering the current state (the 'state' member) during transitons.
This change allows keeping the current state unchanged during the
entire transition chain, which in turn allows easy and generic access
to the state information to store the state history in the exit
actions from states. Additional bonus of this re-design is the 
opportunity of testing for stable state configuration in assertions
added to the qepn.c file.

4. Added the QHsm_state() and QFsm_state() accessor macros.

5. Modified the "Transition to History" pattern implementation to 
use the simplified technique of obtaining the current state in the
exit action from the superstate rather than all the exit actions from
the substates. Modified the "State-Local Storage" (SLS) pattern as
well, because it was using the transition to history constructs. 

6. Modified the QP-nano port to Win32 (both the MinGW and VC2008).

7. Modified the QP-nano port to POSIX.

8. Added QP port to Qt (Qt with one thread) and two example
applications (DPP and PELICAN crossing).

9. Added GNU compiler option -pthread to QP ports for POSIX with
P-threads, including QP ports and examples for Linux and Mac OS X. 


------------------------------------------------------------------------------
@section qpn_4_4_00 Version 4.4.00, 2012-03-03

The main pupose of this relase is MISRA-C:2004 compliance, strong-type
checking compliance, update of PC-Lint option files and tests, and
general cleanup.

1. For commonality with the QP/C and QP/C++ frameworks renamed macros
QF_INT_LOCK/QF_INT_UNLOCK to QF_INT_DISABLE/QF_INT_ENABLE, respectively.
Also renamed macros QF_INT_KEY_TYPE/QF_ISR_LOCK/QF_ISR_UNLOCK to
QF_ISR_STAT_TYPE/QF_ISR_DISABLE/QF_ISR_RESTORE, respectively.

NOTE: This modifications have impact on most QP-nano ports. However,
the qfn.h header file contains definitions of the new macros in terms
of the old ones. This provies backwards comatibility of the existing
QP-nano ports.

2. Added the PC-Lint option files std.lnt and lib-qpn.lnt to the
qcn/include/ directory.
 
3. Cleaned the whole QP-nano code from lint comments. All PC-Lint options
have been moved to PC-Lint option files.
 
4. Modified QP-nano assertion macro Q_DEFINE_THIS_MODULE() to avoid
using the # operator (MISRA rule 19.13). This macro now requires the
argument enclosed in doble quotes "".

NOTE: This modification has impact on some QP-nano ports. 

4. Added typedefs for char_t, int_t, float32_t, and float64_t to
event.h header file for compliance with MISRA-C:2004 rules 6.1 and 6.3.

5. Added macros Q_STATE_CAST() and Q_ACTIVE_CAST() to qep.h to
encapsulate deviation from MISRA-C rule 11.4.

6. Added macro Q_UINT2PTR_CAST() to encapsulate casting unsigned
integers to pointers, which deviates from MISRA-C rule 11.3. This
macro has been added for *application-level* code.

7. Updated ARM Cortex-M examples with the latest CMSIS v3.0, which
complies with more MISRA-C:2004 rules.

8. Added PELICAN examples for MISRA-C:2004 compliant applications (for
IAR-ARM and GNU-ARM).

9. Added testing of PC-Lint option files against the MISRA-C Exemplar
Suite.

10. Updated ARM-Cortex-M3 port with GNU to the latest Sourcery
CodeBench 2011.09-60.

11. Added documentation to QP-nano distribution in the directory
qpn/doc/, with the following Application notes: "QP-nano MISRA-C:2004
Compliance Matrix" and "Quantum Leaps Coding Standard",  


------------------------------------------------------------------------------
@section qpn_4_3_00 Version 4.3.00, 2011-10-31

1. This release changes the partitioning of the QK-nano scheduler.
Specifically, the QK-nano scheduler is now divided between two
functions QK_schedPrio_() and QK_sched_(), to calculate the highest-
priority task ready to run and to perform scheduling, respectively.
The function QK_schedPrio_() is useful to determine if scheduling
is even necessary.

2. Reduced the interrupt latency of the QK-nano kernel by breaking up
the critical section in the QK_sched_() into two pieces, just after
setting QK_currPrio_.

3. Modified the ARM Cortex-M port qkn_port.s to take advantage of the
new structure of the QK-nano scheduler. To reduce code duplications,
the QK-nano port file qkn_port.s has been placed in the directories:
qpn/ports/arm-cortex/qk/gnu/ for the GNU compiler and
qpn/ports/arm-cortex/qk/iar/ for the IAR compiler, respectively.

4. Moved the Win32 and POSIX emulation of QP-nano from the directory
qpn/emulation/ to qpn/ports/win32/ and qpn/ports/posix/, respectively.

5. Renamed the function QF_tick() to QF_tickISR() to clearly notify
the user that this function is callable from ISR only. For backwards
compatibility, the macro QF_tick() is defined to QF_tickISR().

6. Modified QF_tickISR(), QActive_postISR(), QActive_post(), and
QK_sched_() to use stack-based pointer to QActiveCB, which avoids
re-computation of the pointer on-the-fly in the loop. According to the
feature request #3403079, this significantly speeds up the code for
8-bit PIC micros.

7. Upgraded the examples for ARM Cortex with IAR EWARM to the
latest IAR EWARM Version 6.30.

8. Upgraded the examples for ARM Cortex with GNU (CodeSourcery) to the
latest Sourcery CodeBench 2011.07-60.


------------------------------------------------------------------------------
@section qpn_4_2_04 Version 4.2.04, 2011-09-24

The main pupose of this relase is to provide a bug fix for the QK port
to ARM Cortex processors. The bug fix addresses a very rare and
undocumented behavior of late-arrival of an interrupt while entering
the PendSV exception. In this case the PENDSVSET bit in the NVIC-ICSR
register is *not* cleared when finally PendSV is entered, so the
PendSV exception is entered in a *different* state when it is entered
via the late-arrival mechanism versus the normal activation of the
exception through tail-chaining. The consequence of this undocumented
and inconsistent hardware behavior, PendSV could be re-entered again
before the SVCall exception cleans up the stack. The bug fix is
implemented in the qk_port.s file (in QP-nano this file is replicated
in every example for QK-nano) and consists of clearing the PENDSVSET
bit programmatically inside PendSV_Handler.


------------------------------------------------------------------------------
@section qpc_4_2_02 Version 4.2.02, 2011-09-08

The main pupose of this relase is to repackage the default QP-nano
distribution to contain the single root directory qpn/ in the
archive. That way, unziping the archive will produce only one
directory (qpn/), which can be then changed by the user.


------------------------------------------------------------------------------
@section qpn_4_2_01 Version 4.2.01, 2011-08-13

1. Modified file qassert.h to add assertion macros #Q_ASSERT_ID,
#Q_REQUIRE_ID, #Q_ENSURE_ID, #Q_INVARIANT_ID, and #Q_ERROR_ID,
which are better suited for unit testig, because they avoid the
volatility of line numbers for indentifying assertions.

2. Modified the make files and project files to use the environment
variable QPN instead of relying on the relative path to the QP-nano
framework.

3. Added QP-nano examples for Mac OS X on 80x86.

4. Upgraded the examples for ARM Cortex with IAR EWARM to the
latest IAR EWARM Version 6.20.

5. Upgraded the examples for MSP430 with IAR EW430 to the
latest IAR EW430 Version 5.30.


------------------------------------------------------------------------------
@section qpn_4_1_07 Version 4.1.07, 2011-02-28

The goal of this release is to improve the ease of experimenting with
QP-nano on the desktop. This release adds support for Windows (Win32)
and Linux to the QP-nano baseline code. Two most popular compilers for
Windows are supported: Microsoft Visual Studio and MinGW (GNU). The
support for Linux includes pre-built examples and makefiles compatible
with Eclipse.

The changes in detail are:

1. Added sub-directory qpn/emulation with emulation code for Windows
(win32) and POSIX (Linux, Mac OS X, etc.). 

2. Added Win32 examples for Visual C++ 2008 (examples/80x86/win32/
vc2008/dpp and examples/80x86/win32/vc2008/qhsmtst). Visual Studio
soultions are provides for all build configurations.

3. Added Win32 examples for MinGW (examples/80x86/win32/mingw/dpp
and examples/80x86/win32/mingw/qhsmtst). Eclipse-compatible makefiles
are provided for all build configurations. NOTE: the Makefiles assume
that the MinGW/bin directory is added to the PATH.

4. Fixed a bug in file qfn.c, function QActive_postISR(). For special
rare combination of configuration macros the assertion was checked 
before declaring an automatic variable QF_ISR_KEY_TYPE key. This
declaration has been moved to the top of the function.

5. Upgraded the examples for ARM Cortex with CodeSourcery to the
latest Sourcery G++ 2011.02-2.


------------------------------------------------------------------------------
@section qpn_4_1_06 Version 4.1.06, 2011-01-07

1. Made cosmetic improvements to the example QM model of the
"Fly 'n' Shoot" game. 

2. Made improvements in make.bat files for building the examples for
DOS/Open Watcom to run better in DosBox on Linux.

3. Upgraded the examples for ARM Cortex with IAR to the latest
IAR EWARM Version 6.10.

4. Upgraded the examples for ARM Cortex with CodeSourcery to the
latest Sourcery G++ 2010.09-66.


------------------------------------------------------------------------------
@section qpn_4_1_05 Version 4.1.05 (Product) Nov 01, 2010

This release is adds examples for the QM (QP Modeler) graphical modeling
and code generation tool. The examples are based on the "Fly 'n' Shoot"
game described in the QP-nano Tutorial and in Chapter 1 of the PSiCC2 book.

Specifically, the directory qpn/examples/80x86/watcom/game-qm/
contains the "Fly 'n' Shoot" game model file "game.qm". This model, when
opened in the QM tool contains all state machine diagrams and generates
code into the subdirectory qm_code/. This code can then be built and
executed on any 80x86 machine (newer versions of Windows or Linux require
the DOSbox application, see http://www.dosbox.com).

The directory qpn/examples/arm-cortex/iar/game-ev-lm3s811-qm/
contains the Version of the game for the EV-LM3S811 ARM Cortex-M3 board.
This directory contains the model file "game.qm", which is actually
identical as the model in the DOS version. The LM3S811 Version needs to
be compiled with the IAR compiler and executed on the EV-LM3S811 board.

Additionally, the QP-nano baseline code has been slighlty modified for
better conformance to the MISRA C 2004 rules and the latest PC-Lint 9.x. 


------------------------------------------------------------------------------
@section qpn_4_1_04 Version 4.1.04, 2010-03-16

This release is adds compatibility of all examples for DOS with the DOSBox
emulator (http://www.dosbox.com/) that recreates a MS-DOS compatible
environment on all versions of Windows, including 64-bit Windows that don't
run 16-bit DOS applications anymore.

Also, this release includes QP ports and examples for EV-LM3S811 board with
the GNU-based Code Sourcery G++ toolset. Support for Sourcery G++ provides
a very cost-effective option for developing QP applications for ARM Cortex
MCUs. 

Finally, this release improves the Cortex Microcontroller Software Interface
Standard (CMSIS) for the whole family of the Stellaris LM3Sxxx MCUs. The
improvement extends the CMSIS from Sandstorm to Fury, DustDevil, and Tempest
Stellaris families.  


------------------------------------------------------------------------------
@section qpn_4_1_03 Version 4.1.03, 2010-01-21

This release is concerned with the ARM Cortex ports and examples.
Specifically, this release contains the following improvements:

1. Unified source code for ARM Cortex-M3 and the new ARM Cortex-M0 cores,
including the code for the preemptive QK kernel.

2. Compliance with the Cortex Microcontroller Software Interface Standard
(CMSIS) in all ARM Cortex examples.

3. Backward-compatible support for the new LM3S811 EVAL Rev C board with
different OLED display than previous revisions. (NOTE: The OSRAM 96x16x1 OLED
used in REV A-B boards has been replaced RITEK 96x16x1 OLED used in Rev C.)

In the process of making the examples CMSIS-compliant, the dependency on the
Luminary Micro driver library (driverlib.a) has been completely removed.

Additionally, the screen saver of the "Fly 'n' Shoot" game has been improved
to periodically switch off the power of the OLED display, which better
protects the display from burn-in. The affected file is tunnel.c.

Finally, this release introduces the QP_Version macro, which identifies the QP
version. Otherwise, this maintenance release does not change the QP/C API in
any way, so the release has NO IMPACT on the QP/C applications except for the
ARM Cortex ports and applications. 


------------------------------------------------------------------------------
@section qpn_4_1_02 Version 4.1.02, 2010-01-14

The purpose of this minor maintenance release is the change in the directory
structure for the ARM Cortex ports and examples. As new ARM Cortex cores are
becoming available, the old port name "cortex-m3" could be misleading, because
it actually applies to wider range of ARM Cortex cores. Consequently, all ARM
Cortex ports and examples are hosted in the directory tree called
"arm-cortex".

This maintenance release does not change the QP-nano API in any way, so the
release has NO IMPACT on the QP-nano applications except for the ARM Cortex
ports and applications. 


------------------------------------------------------------------------------
@section qpn_4_1_01 Version 4.1.01, 2009-11-05

The main purpose of this release is to replace the Turbo C++ 1.01 toolset
with the Open Watcom C/C++ toolset, because Turbo C++ 1.01 is no longer
available for a free download. In contrast, Open Watcom is distributed under
an OSI-certified open source license, which permits free commercial and
non-commercial use. Open Watcom can be downloaded from www.openwatcom.org.

All 80x86 examples (vanilla and QK-nano) for Turbo C++ 1.01 have been replaced
with examples for Open Watcom. The make.bat scripts are provided to build the
examples. 

In the process of converting the examples to Open Watcom a new SLS example
have been added to the standard QP-nano distribution. The SLS example located
in &lt;qpn&gt;/examples/80x86/watcom/sls/ shows the QP-nano implemenation of the
new State-Local Storage state design pattern.


------------------------------------------------------------------------------
@section qpn_4_1_00 Version 4.1.00, 2009-10-09

The main purpose of this release is to fix a bug in event posting, which
could cause corruption of the event signal. Such corruption could occur when
an event was posted to an empty event queue, in which case it was written
directly to the internal event stored in the state machine, bypassing the
ring-buffer. However, the signal of the internal event could also be changed
by the QEP-nano event processor during execution of transitions.

The bug fix is to always pass events through the ring buffer and never
overwrite the internal event during event posting (both from the task
level and from the ISR level). The update of the ring buffer always
occurs within a critical section and is safe from interruptions. 

This bug fix also allows posting of events from the top-most initial
transitions of active objects during the initialization phase. Previously,
the execution of the top-most initial transition corrupted the signal of
the internal event.

The bug fix enables also self-posting of events from entry/exit actions
and internal initial transitions. Again, the QEP event processor corrupted
the internal signal.

This release also replaces the static variables 'p' (priority) and 'a'
(active object pointer) with automatic variables. This change results in
more efficient code, because the frequently used variables can be kept in
registers and do not need to be read/written from/to memory by each use.  

Additionally, this release updates the QP-nano ARM Cortex-M3 examples for
the EK-LM3S811 board to the latest IAR EWARM 5.40. Due to the acquisition
of Liminary Micro by Texas Instruments the directory IAR structure for the
examples and drivers has changed and the QP-nano examples had to be changed
accordingly.

Finally, this release fixes a bug in the "Fly 'n' Shoot" game example for
QP-nano, which caused an assertion if the Ship was moved to the very top
of the Tunnel. This was due to the y-coordinate of the ship explosion
becomoming negative.   

NOTE: This release does not change the QP-nano API, but all event queues
are effectively shortened by one event. Also it is no longer possible to
declare an active object without a ring buffer (zero-sized queue), because
the internal event no longer counts towards the queue depth.

The main changes in QP v4.1.00 with respect to the earlier versions are
as follows:

- modified functions QActive_post(), QActive_postISR(), and QF_run() in qfn.c
to always use the ring buffer and not to count the internal event as part
of the queue (in the assertions).   
- modified qfn.c to replace static variables 'p' and 'a' with automatic
variables.
- modified function QK_schedule_() in qkn.c to always use the ring buffer,
as described above.
- modified module qkn.c to to replace static variables 'p' and 'l_act' with
automatic variables.
- modified various examples to eliminate zero-sized queues and extend event
queues by one event.
- modified the ARM Cortex-M3 examples for the new IAR EWARM 5.40.
- modified the ship.c and tunnel.c files in the "Fly 'n' Shoot" game
example to fix the aforementioned bug.


------------------------------------------------------------------------------
@section qpn_4_0_04 Version 4.0.04, 2009-04-09

The maintenance release provides a fix for the compile-time assertions,
which did not work correctly for the GNU compiler family. Also, the ARM
Cortex-M3 examples have been recompiled with the newer IAR EWARM v5.30.

This maintenance release does not change the QP-nano API in any way, so the
release has NO IMPACT on the QP-nano applications. 

The main changes in QP v4.0.04 with respect to earlier Version are as follows:

- in qassert.h file the #Q_ASSERT_COMPILE macro has been modified to render
a negative array dimension when the asserted condition is not TRUE.


------------------------------------------------------------------------------
@section qpn_4_0_03 Version 4.0.03, 2008-08-06

The main purpose of this release is to "future-proof" the QK-nano preemptive
kernel. The release 4.0.03 strictly preserves the semantics of QK_currPrio_
variable, which was violated by the previous QK mutex implementation.
The mutex locking now uses a different variable QK_ceilingPrio_, which
represents the ceiling-priority locked by the mutex. When the mutex is
configured (the macro #QK_MUTEX is defined), the QK-nano scheduler
performs an additional check to make sure that only tasks with priorities
above the ceiling can run. This additional overhead is not present when
#QK_MUTEX is not defined.

This maintenance release does not change the QP-nano API in any way, so the
release has NO IMPACT on the QP-nano applications. 

The main changes in QP v4.0.03 with respect to earlier Version are as follows:

- in qkn.c file, changed priority-ceiling mutex implementation to use
the QK_ceilingPrio_ instead of QK_currPrio_. Also added testing priority
against the QK_ceilingPrio_, when the macro QK_MUTEX is defined.


------------------------------------------------------------------------------
@section qpn_4_0_02 Version 4.0.02, 2008-08-06

This maintenace release is made to allow posting events from any active object
to any active object from the top-most initial transtions.

This maintenance release does not change the QP-nano API in any way, so the
release has NO IMPACT on the QP-nano applications. 

The main changes in QP v4.0.02 with respect to earlier Version are as follows:

- modified function QF_run() in qfn.c to first loop over all active objects
and initialize their priority attribute based on their location in the
QF_active[] array. The second for-loop triggers only the initial transitions,
but now all priorities are initialized, so active objects can post events to
each others from the initial transitions.  
- modified function QF_run() in qkn.c in identical way as in qfn.c described
above.


------------------------------------------------------------------------------
@section qpn_4_0_01 Version 4.0.01, 2008-06-08

This maintenace release is made to allow compiling QP-nano with the GNU
compiler for AVR (WinAVR). Specifically, some changes were necessary to
accomodate the non-standard way of hanlding constant data objects allocated
in ROM (PROGMEM) in the GNU compiler for AVR.

This maintenance release does not change the QP-nano API in any way, so the
release has NO IMPACT on the QP-nano applications. 

The main changes in QP v4.0.01 with respect to earlier Version are as follows:

- eliminated QF_pCB_ variable from qfn.c and qkn.c. This variable was used to
point to the constant active object control block (QActiveCB) in ROM. The GNU
compliler for AVR could not handle such pointer correctly without
contaminating the code with non-portable and non-standard extensions.

- added Doxygen comments to the qep.h header file.

- in qepn.c file, broken up expressions of the form if (t == path[iq]) ...
into (s = path[iq]; if (t == s) ...). This was done to accommodate the
ImageCraft ICCM8C compiler for PSoC.  

------------------------------------------------------------------------------
@section qpn_4_0_00 Version 4.0.00, 2008-04-07

This milestone release is made for the book /ref PSiCC2. The book describes in
great detail this new release. The older "QP-nano Programmer's Manual" is now
phased out and is replaced with this hyper-lirenked
/ref main_page "QP-nano Reference Manual", which provides very detailed,
easily searchable reference to the software. The book /ref PSiCC2 provies
in-depth discussion of the relevant concepts as well as the design study of
QP v4.0, including QP-nano v4.0 in Chapter 12.

The main changes in QP v4.0 with respect to earlier versions are as follows:

- the coding techniques for hierarchical state machines (HSMs) and the simpler
finite state machines (FSMs) have changed. While the changes are quite simple,
the backward compatibility with QEP-nano 3.x has been broken, meaning that
some manual changes to the state machines implemented with earlier versions
are necessary. Please refer to the "QP-nano Tutorial" Section /ref coding_hsm
for more information about coding state machines with QEP 4.x.
    - The main change is the signature of a state-handler function, which now
    returns simply a byte. This return type (typedef'ed as QState) is the
    status of the event-handling that the state handler conveys to the QEP
    event processor.
    - The macro #Q_TRAN() must now always follow the return statement.
    - The new macro #Q_SUPER() designates the superstate of the given state.
    Again, this macro must follow the return statement.
    - Then two new macros #Q_HANDLED() and #Q_IGNORED() have been added to
    return the status of event handled and event ignored, respectively.

- all callback functions are now consistently called /c #XXX_onYYY():
    - Q_assert_handler() is now Q_onAssert()
    - QF_start() is now QF_onStartup()
    - QF_cleanup() is now QF_onCleanup()

- all callback functions are now consistently called /c XXX_onYYY():
    - Q_assert_handler() is now Q_onAssert()
    - QF_start() is now QF_onStartup()
    - QF_cleanup() is now QF_onCleanup()
- enumerating global active object priorities is no longer necessary.
- the methods of posting events have changed:
    - QF_post(prio, sig, par) is now void QActive_post(me, sig, par)    
    - QF_postISR(prio, sig, par) is now void QActive_postISR(me, sig, par)
- the global variable QF_activeNum has been eliminated
    - instead the constant #QF_MAX_ACTIVE <STRONG>must</STRONG> correspond
      to the exact number of active objects in the application.
- the QEP-nano event processor now works identically as the full-Version QEP.
Specifically, the signal of the current event is not used to notify the event
processor that a transition has taken place. This saves a few bytes of code
for every usage of #Q_TRAN().
- all QF-nano and QK-nano functions have been modified to use static variables
instead of stack variables wherever possible. This saves a few bytes of stack
for the "vanilla" kernel. In QK-nano the savings can be more substantial.
- the QP-nano event queues now decrement the head and tail counters. This
leads to wrap-around at zero, which is easier (faster) to test than any other
wrap-around point.
- all examples in the standard QP-nano distribution have been cleaned up and
updated to the latest QP-nano API changes.
*/


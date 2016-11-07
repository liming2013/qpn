/*****************************************************************************
* Model: pelican.qm
* File:  ./pelican.c
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::pelican.c} ..........................................................*/
#include "qpn.h"     /* QP-nano */
#include "bsp.h"     /* Board Support Package (BSP) */
#include "pelican.h" /* application interface */

/*Q_DEFINE_THIS_FILE*/

#define CARS_GREEN_MIN_TOUT (QTimeEvtCtr)(BSP_TICKS_PER_SEC * 8U)
#define CARS_YELLOW_TOUT    (QTimeEvtCtr)(BSP_TICKS_PER_SEC * 3U)
#define PEDS_WALK_TOUT      (QTimeEvtCtr)(BSP_TICKS_PER_SEC * 3U)
#define PEDS_FLASH_TOUT     (QTimeEvtCtr)(BSP_TICKS_PER_SEC / 5U)
#define PEDS_FLASH_NUM      (uint8_t)(5U * 2U)
#define OFF_FLASH_TOUT      (QTimeEvtCtr)(BSP_TICKS_PER_SEC / 2U)

/* Pelican class declaration -----------------------------------------------*/
/*${components::Pelican} ...................................................*/
typedef struct Pelican {
/* protected: */
    QActive super;

/* private: */
    uint8_t flashCtr;
} Pelican;

/* protected: */
static QState Pelican_initial(Pelican * const me);
static QState Pelican_operational(Pelican * const me);
static QState Pelican_carsEnabled(Pelican * const me);
static QState Pelican_carsGreen(Pelican * const me);
static QState Pelican_carsGreenNoPed(Pelican * const me);
static QState Pelican_carsGreenInt(Pelican * const me);
static QState Pelican_carsGreenPedWait(Pelican * const me);
static QState Pelican_carsYellow(Pelican * const me);
static QState Pelican_pedsEnabled(Pelican * const me);
static QState Pelican_pedsWalk(Pelican * const me);
static QState Pelican_pedsFlash(Pelican * const me);
static QState Pelican_offline(Pelican * const me);


/* Global objects ----------------------------------------------------------*/
struct Pelican AO_Pelican; /* the single instance of the Pelican AO */

/* Pelican class definition ------------------------------------------------*/
/*${components::Pelican_ctor} ..............................................*/
void Pelican_ctor(void) {
    QActive_ctor(&AO_Pelican.super, Q_STATE_CAST(&Pelican_initial));
}
/*${components::Pelican} ...................................................*/
/*${components::Pelican::SM} ...............................................*/
static QState Pelican_initial(Pelican * const me) {
    /* ${components::Pelican::SM::initial} */
    return Q_TRAN(&Pelican_operational);
}
/*${components::Pelican::SM::operational} ..................................*/
static QState Pelican_operational(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational} */
        case Q_ENTRY_SIG: {
            BSP_signalCars(CARS_RED);
            BSP_signalPeds(PEDS_DONT_WALK);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Pelican_carsEnabled);
            break;
        }
        /* ${components::Pelican::SM::operational::OFF} */
        case OFF_SIG: {
            status_ = Q_TRAN(&Pelican_offline);
            break;
        }
        /* ${components::Pelican::SM::operational::TERMINATE} */
        case TERMINATE_SIG: {
            QF_stop();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled} .....................*/
static QState Pelican_carsEnabled(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled} */
        case Q_EXIT_SIG: {
            BSP_signalCars(CARS_RED);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Pelican_carsGreen);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_operational);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled::carsGreen} ..........*/
static QState Pelican_carsGreen(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen} */
        case Q_ENTRY_SIG: {
            BSP_signalCars(CARS_GREEN);
            /* one-shot timeout in CARS_GREEN_MIN_TOUT ticks */
            QActive_armX(&me->super, 0U, CARS_GREEN_MIN_TOUT, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Pelican_carsGreenNoPed);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_carsEnabled);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenNoPed} */
static QState Pelican_carsGreenNoPed(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenNoPed} */
        case Q_ENTRY_SIG: {
            BSP_showState("carsGreenNoPed");
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenNoPed::PEDS_WAITING} */
        case PEDS_WAITING_SIG: {
            status_ = Q_TRAN(&Pelican_carsGreenPedWait);
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenNoPed::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Pelican_carsGreenInt);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_carsGreen);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenInt} */
static QState Pelican_carsGreenInt(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenInt} */
        case Q_ENTRY_SIG: {
            BSP_showState("carsGreenInt");
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenInt::PEDS_WAITING} */
        case PEDS_WAITING_SIG: {
            status_ = Q_TRAN(&Pelican_carsYellow);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_carsGreen);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenPedWait} */
static QState Pelican_carsGreenPedWait(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenPedWait} */
        case Q_ENTRY_SIG: {
            BSP_showState("carsGreenPedWait");
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsGreen::carsGreenPedWait::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Pelican_carsYellow);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_carsGreen);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::carsEnabled::carsYellow} .........*/
static QState Pelican_carsYellow(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::carsEnabled::carsYellow} */
        case Q_ENTRY_SIG: {
            BSP_showState("carsYellow");
            BSP_signalCars(CARS_YELLOW);

            /* one-shot timeout in CARS_YELLOW_TOUT ticks */
            QActive_armX(&me->super, 0U, CARS_YELLOW_TOUT, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsYellow} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::carsEnabled::carsYellow::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Pelican_pedsEnabled);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_carsEnabled);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::pedsEnabled} .....................*/
static QState Pelican_pedsEnabled(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::pedsEnabled} */
        case Q_EXIT_SIG: {
            BSP_signalPeds(PEDS_DONT_WALK);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::pedsEnabled::initial} */
        case Q_INIT_SIG: {
            status_ = Q_TRAN(&Pelican_pedsWalk);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_operational);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::pedsEnabled::pedsWalk} ...........*/
static QState Pelican_pedsWalk(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsWalk} */
        case Q_ENTRY_SIG: {
            BSP_showState("pedsWalk");
            BSP_signalPeds(PEDS_WALK);
            /* one-shot timeout in PEDS_WALK_TOUT ticks */
            QActive_armX(&me->super, 0U, PEDS_WALK_TOUT, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsWalk} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsWalk::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Pelican_pedsFlash);
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_pedsEnabled);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::operational::pedsEnabled::pedsFlash} ..........*/
static QState Pelican_pedsFlash(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash} */
        case Q_ENTRY_SIG: {
            BSP_showState("pedsFlash");
            /* periodic timeout in PEDS_FLASH_TOUT and every PEDS_FLASH_TOUT ticks */
            QActive_armX(&me->super, 0U, PEDS_FLASH_TOUT, PEDS_FLASH_TOUT);
            me->flashCtr = (PEDS_FLASH_NUM * 2U) + 1U;
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash::Q_TIMEOUT::[me->flashCtr!=0U]} */
            if (me->flashCtr != 0U) {
                --me->flashCtr;
                /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash::Q_TIMEOUT::[me->flashCtr!=0~::[(me->flashCtr&1U)==0U]} */
                if ((me->flashCtr & 1U) == 0U) {
                    BSP_signalPeds(PEDS_DONT_WALK);
                    status_ = Q_HANDLED();
                }
                /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash::Q_TIMEOUT::[me->flashCtr!=0~::[else]} */
                else {
                    BSP_signalPeds(PEDS_BLANK);
                    status_ = Q_HANDLED();
                }
            }
            /* ${components::Pelican::SM::operational::pedsEnabled::pedsFlash::Q_TIMEOUT::[else]} */
            else {
                status_ = Q_TRAN(&Pelican_carsEnabled);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Pelican_pedsEnabled);
            break;
        }
    }
    return status_;
}
/*${components::Pelican::SM::offline} ......................................*/
static QState Pelican_offline(Pelican * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${components::Pelican::SM::offline} */
        case Q_ENTRY_SIG: {
            BSP_showState("offline");
            /* periodic timeout in OFF_FLASH_TOUT and every OFF_FLASH_TOUT ticks */
            QActive_armX(&me->super, 0U, OFF_FLASH_TOUT, OFF_FLASH_TOUT);
            me->flashCtr = 0U;
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::offline} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${components::Pelican::SM::offline::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            me->flashCtr ^= 1U;
            /* ${components::Pelican::SM::offline::Q_TIMEOUT::[(me->flashCtr&1U)==0U]} */
            if ((me->flashCtr & 1U) == 0U) {
                BSP_signalCars(CARS_RED);
                BSP_signalPeds(PEDS_DONT_WALK);
                status_ = Q_HANDLED();
            }
            /* ${components::Pelican::SM::offline::Q_TIMEOUT::[else]} */
            else {
                BSP_signalCars(CARS_BLANK);
                BSP_signalPeds(PEDS_BLANK);
                status_ = Q_HANDLED();
            }
            break;
        }
        /* ${components::Pelican::SM::offline::ON} */
        case ON_SIG: {
            status_ = Q_TRAN(&Pelican_operational);
            break;
        }
        /* ${components::Pelican::SM::offline::TERMINATE} */
        case TERMINATE_SIG: {
            QF_stop();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}


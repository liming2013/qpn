/*****************************************************************************
* Model: dpp.qm
* File:  ./philo.c
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
/*${.::philo.c} ............................................................*/
#include "qpn.h"  /* QP-nano port */
#include "bsp.h"  /* Board Support Package */
#include "dpp.h"  /* Application interface */

Q_DEFINE_THIS_MODULE("philo")

/* Active object class -----------------------------------------------------*/
/*${AOs::Philo} ............................................................*/
typedef struct Philo {
/* protected: */
    QActive super;
} Philo;

/* protected: */
static QState Philo_initial(Philo * const me);
static QState Philo_thinking(Philo * const me);
static QState Philo_hungry(Philo * const me);
static QState Philo_eating(Philo * const me);


/* Global objects ----------------------------------------------------------*/
/*${AOs::AO_Philo0} ........................................................*/
struct Philo AO_Philo0;

/*${AOs::AO_Philo1} ........................................................*/
struct Philo AO_Philo1;

/*${AOs::AO_Philo2} ........................................................*/
struct Philo AO_Philo2;

/*${AOs::AO_Philo3} ........................................................*/
struct Philo AO_Philo3;

/*${AOs::AO_Philo4} ........................................................*/
struct Philo AO_Philo4;


/* Local objects -----------------------------------------------------------*/
#define THINK_TIME  \
    (QTimeEvtCtr)((BSP_random() % BSP_TICKS_PER_SEC) + (BSP_TICKS_PER_SEC/2U))
#define EAT_TIME    \
    (QTimeEvtCtr)((BSP_random() % BSP_TICKS_PER_SEC) + BSP_TICKS_PER_SEC)

/* Philo definition --------------------------------------------------------*/
/*${AOs::Philo_ctor} .......................................................*/
void Philo_ctor(void) {
    QActive_ctor(&AO_Philo0.super, Q_STATE_CAST(&Philo_initial));
    QActive_ctor(&AO_Philo1.super, Q_STATE_CAST(&Philo_initial));
    QActive_ctor(&AO_Philo2.super, Q_STATE_CAST(&Philo_initial));
    QActive_ctor(&AO_Philo3.super, Q_STATE_CAST(&Philo_initial));
    QActive_ctor(&AO_Philo4.super, Q_STATE_CAST(&Philo_initial));
    BSP_randomSeed(123U);
}
/*${AOs::Philo} ............................................................*/
/*${AOs::Philo::SM} ........................................................*/
static QState Philo_initial(Philo * const me) {
    /* ${AOs::Philo::SM::initial} */
    return Q_TRAN(&Philo_thinking);
}
/*${AOs::Philo::SM::thinking} ..............................................*/
static QState Philo_thinking(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${AOs::Philo::SM::thinking} */
        case Q_ENTRY_SIG: {
            QActive_armX(&me->super, 0U, THINK_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${AOs::Philo::SM::thinking} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${AOs::Philo::SM::thinking::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_hungry);
            break;
        }
        /* ${AOs::Philo::SM::thinking::EAT, DONE} */
        case EAT_SIG: /* intentionally fall through */
        case DONE_SIG: {
            Q_ERROR(); /* these events should never arrive in this state */
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
/*${AOs::Philo::SM::hungry} ................................................*/
static QState Philo_hungry(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${AOs::Philo::SM::hungry} */
        case Q_ENTRY_SIG: {
            QACTIVE_POST(&AO_Table, HUNGRY_SIG, me->super.prio);
            status_ = Q_HANDLED();
            break;
        }
        /* ${AOs::Philo::SM::hungry::EAT} */
        case EAT_SIG: {
            status_ = Q_TRAN(&Philo_eating);
            break;
        }
        /* ${AOs::Philo::SM::hungry::DONE} */
        case DONE_SIG: {
            Q_ERROR(); /* this event should never arrive in this state */
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
/*${AOs::Philo::SM::eating} ................................................*/
static QState Philo_eating(Philo * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${AOs::Philo::SM::eating} */
        case Q_ENTRY_SIG: {
            QActive_armX(&me->super, 0U, EAT_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /* ${AOs::Philo::SM::eating} */
        case Q_EXIT_SIG: {
            QActive_disarmX(&me->super, 0U);
            QACTIVE_POST(QF_ACTIVE_CAST(&AO_Table), DONE_SIG, me->super.prio);
            status_ = Q_HANDLED();
            break;
        }
        /* ${AOs::Philo::SM::eating::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_thinking);
            break;
        }
        /* ${AOs::Philo::SM::eating::EAT, DONE} */
        case EAT_SIG: /* intentionally fall through */
        case DONE_SIG: {
            Q_ERROR(); /* these events should never arrive in this state */
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


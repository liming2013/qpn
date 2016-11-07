/*****************************************************************************
* Model: calc.qm
* File:  ./calc.c
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
/*${.::calc.c} .............................................................*/
#include "qpn.h"   /* QP-nano */
#include "bsp.h"   /* Board Support Package */
#include "calc.h"  /* this applicatin */

/*${SMs::Calc} .............................................................*/
typedef struct Calc {
/* protected: */
    QHsm super;

/* private: */
    double operand1;
    uint8_t operator;
} Calc;

/* protected: */
static QState Calc_initial(Calc * const me);
static QState Calc_on(Calc * const me);
static QState Calc_error(Calc * const me);
static QState Calc_negated1(Calc * const me);
static QState Calc_ready(Calc * const me);
static QState Calc_result(Calc * const me);
static QState Calc_begin(Calc * const me);
static QState Calc_operand1(Calc * const me);
static QState Calc_zero1(Calc * const me);
static QState Calc_int1(Calc * const me);
static QState Calc_frac1(Calc * const me);
static QState Calc_opEntered(Calc * const me);
static QState Calc_negated2(Calc * const me);
static QState Calc_operand2(Calc * const me);
static QState Calc_zero2(Calc * const me);
static QState Calc_int2(Calc * const me);
static QState Calc_frac2(Calc * const me);
static QState Calc_final(Calc * const me);


static Calc l_calc;    /* the only instance of the Calc class */

/* global-scope definitions ---------------------------------------*/
QHsm * const the_calc = &l_calc.super; /* "opaque" pointer to HSM */

/*${SMs::Calc_ctor} ........................................................*/
void Calc_ctor(void) {
    Calc *me = &l_calc;
    QHsm_ctor(&me->super, Q_STATE_CAST(&Calc_initial));
}
/*${SMs::Calc} .............................................................*/
/*${SMs::Calc::SM} .........................................................*/
static QState Calc_initial(Calc * const me) {
    /* ${SMs::Calc::SM::initial} */
    BSP_clear();
    return Q_TRAN(&Calc_on);
}
/*${SMs::Calc::SM::on} .....................................................*/
static QState Calc_on(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on} */
        case Q_ENTRY_SIG: {
            BSP_message("on-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on} */
        case Q_EXIT_SIG: {
            BSP_message("on-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::initial} */
        case Q_INIT_SIG: {
            BSP_message("on-INIT;");
            status_ = Q_TRAN(&Calc_ready);
            break;
        }
        /* ${SMs::Calc::SM::on::C} */
        case C_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_on);
            break;
        }
        /* ${SMs::Calc::SM::on::OFF} */
        case OFF_SIG: {
            status_ = Q_TRAN(&Calc_final);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::error} ..............................................*/
static QState Calc_error(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::error} */
        case Q_ENTRY_SIG: {
            BSP_message("error-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::error} */
        case Q_EXIT_SIG: {
            BSP_message("error-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::negated1} ...........................................*/
static QState Calc_negated1(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::negated1} */
        case Q_ENTRY_SIG: {
            BSP_message("negated1-ENTRY;");
            BSP_negate();
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::negated1} */
        case Q_EXIT_SIG: {
            BSP_message("negated1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::negated1::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_zero1);
            break;
        }
        /* ${SMs::Calc::SM::on::negated1::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /* ${SMs::Calc::SM::on::negated1::POINT} */
        case POINT_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /* ${SMs::Calc::SM::on::negated1::OPER} */
        case OPER_SIG: {
            /* ${SMs::Calc::SM::on::negated1::OPER::[e->key=='-']} */
            if (Q_PAR(me) == KEY_MINUS) {
                ;
                status_ = Q_HANDLED();
            }
            /* ${SMs::Calc::SM::on::negated1::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        /* ${SMs::Calc::SM::on::negated1::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::ready} ..............................................*/
static QState Calc_ready(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::ready} */
        case Q_ENTRY_SIG: {
            BSP_message("ready-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::ready} */
        case Q_EXIT_SIG: {
            BSP_message("ready-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::ready::initial} */
        case Q_INIT_SIG: {
            BSP_message("ready-INIT;");
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        /* ${SMs::Calc::SM::on::ready::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_zero1);
            break;
        }
        /* ${SMs::Calc::SM::on::ready::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_clear();
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /* ${SMs::Calc::SM::on::ready::POINT} */
        case POINT_SIG: {
            BSP_clear();
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /* ${SMs::Calc::SM::on::ready::OPER} */
        case OPER_SIG: {
            me->operand1 = BSP_get_value();
            me->operator = Q_PAR(me);
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::ready::result} ......................................*/
static QState Calc_result(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::ready::result} */
        case Q_ENTRY_SIG: {
            BSP_message("result-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::ready::result} */
        case Q_EXIT_SIG: {
            BSP_message("result-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_ready);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::ready::begin} .......................................*/
static QState Calc_begin(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::ready::begin} */
        case Q_ENTRY_SIG: {
            BSP_message("begin-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::ready::begin} */
        case Q_EXIT_SIG: {
            BSP_message("begin-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::ready::begin::OPER} */
        case OPER_SIG: {
            /* ${SMs::Calc::SM::on::ready::begin::OPER::[e->key=='-']} */
            if (Q_PAR(me) == KEY_MINUS) {
                status_ = Q_TRAN(&Calc_negated1);
            }
            /* ${SMs::Calc::SM::on::ready::begin::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_ready);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand1} ...........................................*/
static QState Calc_operand1(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand1} */
        case Q_ENTRY_SIG: {
            BSP_message("operand1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1} */
        case Q_EXIT_SIG: {
            BSP_message("operand1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_begin);
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::OPER} */
        case OPER_SIG: {
            me->operand1 = BSP_get_value();
            me->operator = Q_PAR(me);
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::EQUALS} */
        case EQUALS_SIG: {
            status_ = Q_TRAN(&Calc_result);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand1::zero1} ....................................*/
static QState Calc_zero1(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand1::zero1} */
        case Q_ENTRY_SIG: {
            BSP_message("zero1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::zero1} */
        case Q_EXIT_SIG: {
            BSP_message("zero1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::zero1::DIGIT_0} */
        case DIGIT_0_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::zero1::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int1);
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::zero1::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand1::int1} .....................................*/
static QState Calc_int1(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand1::int1} */
        case Q_ENTRY_SIG: {
            BSP_message("int1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::int1} */
        case Q_EXIT_SIG: {
            BSP_message("int1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::int1::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac1);
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::int1::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand1::frac1} ....................................*/
static QState Calc_frac1(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand1::frac1} */
        case Q_ENTRY_SIG: {
            BSP_message("frac1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::frac1} */
        case Q_EXIT_SIG: {
            BSP_message("frac1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::frac1::POINT} */
        case POINT_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand1::frac1::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand1);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::opEntered} ..........................................*/
static QState Calc_opEntered(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::opEntered} */
        case Q_ENTRY_SIG: {
            BSP_message("opEntered-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::opEntered} */
        case Q_EXIT_SIG: {
            BSP_message("opEntered-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::opEntered::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_zero2);
            break;
        }
        /* ${SMs::Calc::SM::on::opEntered::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_clear();
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /* ${SMs::Calc::SM::on::opEntered::POINT} */
        case POINT_SIG: {
            BSP_clear();
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /* ${SMs::Calc::SM::on::opEntered::OPER} */
        case OPER_SIG: {
            /* ${SMs::Calc::SM::on::opEntered::OPER::[e->key=='-']} */
            if (Q_PAR(me) == KEY_MINUS) {
                status_ = Q_TRAN(&Calc_negated2);
            }
            /* ${SMs::Calc::SM::on::opEntered::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::negated2} ...........................................*/
static QState Calc_negated2(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::negated2} */
        case Q_ENTRY_SIG: {
            BSP_message("negated2-ENTRY;");
            BSP_negate();
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::negated2} */
        case Q_EXIT_SIG: {
            BSP_message("negated2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::negated2::DIGIT_0} */
        case DIGIT_0_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_zero2);
            break;
        }
        /* ${SMs::Calc::SM::on::negated2::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /* ${SMs::Calc::SM::on::negated2::POINT} */
        case POINT_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /* ${SMs::Calc::SM::on::negated2::OPER} */
        case OPER_SIG: {
            /* ${SMs::Calc::SM::on::negated2::OPER::[e->key=='-']} */
            if (Q_PAR(me) == KEY_MINUS) {
                ;
                status_ = Q_HANDLED();
            }
            /* ${SMs::Calc::SM::on::negated2::OPER::[else]} */
            else {
                status_ = Q_HANDLED();
            }
            break;
        }
        /* ${SMs::Calc::SM::on::negated2::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand2} ...........................................*/
static QState Calc_operand2(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand2} */
        case Q_ENTRY_SIG: {
            BSP_message("operand2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2} */
        case Q_EXIT_SIG: {
            BSP_message("operand2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::CE} */
        case CE_SIG: {
            BSP_clear();
            status_ = Q_TRAN(&Calc_opEntered);
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::EQUALS} */
        case EQUALS_SIG: {
            /* ${SMs::Calc::SM::on::operand2::EQUALS::[BSP_eval()]} */
            if (BSP_eval(me->operand1, me->operator, BSP_get_value())) {
                status_ = Q_TRAN(&Calc_result);
            }
            /* ${SMs::Calc::SM::on::operand2::EQUALS::[else]} */
            else {
                status_ = Q_TRAN(&Calc_error);
            }
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::OPER} */
        case OPER_SIG: {
            /* ${SMs::Calc::SM::on::operand2::OPER::[BSP_eval()]} */
            if (BSP_eval(me->operand1, me->operator, BSP_get_value())) {
                status_ = Q_TRAN(&Calc_opEntered);
            }
            /* ${SMs::Calc::SM::on::operand2::OPER::[else]} */
            else {
                status_ = Q_TRAN(&Calc_error);
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_on);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand2::zero2} ....................................*/
static QState Calc_zero2(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand2::zero2} */
        case Q_ENTRY_SIG: {
            BSP_message("zero2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::zero2} */
        case Q_EXIT_SIG: {
            BSP_message("zero2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::zero2::DIGIT_0} */
        case DIGIT_0_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::zero2::DIGIT_1_9} */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_TRAN(&Calc_int2);
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::zero2::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'0');
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand2::int2} .....................................*/
static QState Calc_int2(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand2::int2} */
        case Q_ENTRY_SIG: {
            BSP_message("int2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::int2} */
        case Q_EXIT_SIG: {
            BSP_message("int2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::int2::POINT} */
        case POINT_SIG: {
            BSP_insert((int)'.');
            status_ = Q_TRAN(&Calc_frac2);
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::int2::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::on::operand2::frac2} ....................................*/
static QState Calc_frac2(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::on::operand2::frac2} */
        case Q_ENTRY_SIG: {
            BSP_message("frac2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::frac2} */
        case Q_EXIT_SIG: {
            BSP_message("frac2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::frac2::POINT} */
        case POINT_SIG: {
            ;
            status_ = Q_HANDLED();
            break;
        }
        /* ${SMs::Calc::SM::on::operand2::frac2::DIGIT_0, DIGIT_1_9} */
        case DIGIT_0_SIG: /* intentionally fall through */
        case DIGIT_1_9_SIG: {
            BSP_insert(Q_PAR(me));
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Calc_operand2);
            break;
        }
    }
    return status_;
}
/*${SMs::Calc::SM::final} ..................................................*/
static QState Calc_final(Calc * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /* ${SMs::Calc::SM::final} */
        case Q_ENTRY_SIG: {
            BSP_message("final-ENTRY;");
            BSP_exit();
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


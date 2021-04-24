/**
 * @file
 * Some macros to facilitate the use of observers.
 * For example, as they are template, calling parent methods can be tedious without "using".
 */

#pragma once

/// Do not works with zero arguments
#define COUNT(...) COUNT_2(__VA_ARGS__, 3, 2, 1)
#define COUNT_2(_, a3, a2, a1, ...) a1

#define EXPAND(...) __VA_ARGS__

/**
 * To insert at the beginning of a class inheriting obs::Subject, for each type of event.
 * Without last semicolon to make the user add it.
 */
#define SUBJECT_1(EventClass)\
public:\
    using obs::Subject<EventClass>::notify;\
    using obs::Subject<EventClass>::attachObserver;\
    using obs::Subject<EventClass>::detachObserver;

#define SUBJECT_2(x, ...) SUBJECT_1(x) SUBJECT_1(__VA_ARGS__)
#define SUBJECT_3(x, ...) SUBJECT_1(x) SUBJECT_2(__VA_ARGS__)
#define SUBJECT_EXP_2(call, n, ...) call##n(__VA_ARGS__)
#define SUBJECT_EXP(call, n, ...) SUBJECT_EXP_2(call, n, __VA_ARGS__)
#define SUBJECT(...) SUBJECT_EXP(SUBJECT_, COUNT(__VA_ARGS__), __VA_ARGS__)
 /**
 * utility.h
 *
 *  \brief     Utilities and helpers for projects. e.g. macros for debugging purpose
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      14.02.2022
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef PLATFORM_FRAMEWORK_INC_UTILITY_H_
#define PLATFORM_FRAMEWORK_INC_UTILITY_H_

#ifndef ALIGN32SIZE

/*!
 * \def ALLIGN32SIZE(type, mult)
 * Computes the number of 32 Bit words required to store  \a mult instances of \a type datatype elements.
 * This macro can be used to compute word aligned memory size for placement new.
 * Example:\n
 * \code
 * uint32_t m_entryMem[ALLIGN32SIZE(entry, 2)]; \n
 * \endcode
 * Allocates a word aligned array capable to store 2  elements of example type entry
 */
#define ALIGN32SIZE(type, mult) ((sizeof(type)+sizeof(uint32_t)-1) / sizeof(uint32_t) *(mult) )
#endif


#ifndef BUILD_BUG_ON_ZERO
   //#ifdef DEBUG
        /*!
         * \def  BUILD_BUG_ON_ZERO(e)
         *  Force a compilation error if condition \a e is true, but also produce a
         *  result (of value 0 and type size_t), so the expression can be used
         *  e.g. in a structure initializer (or where-ever else comma expressions
         *  aren't permitted).
        */
        #define BUILD_BUG_ON_ZERO(e) {struct t_{ int:-!!(e); };(void)sizeof(t_);}
        #define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))
    //#else
    //    #define BUILD_BUG_ON_ZERO(e) (void)(e)
    //    #define BUILD_BUG_ON_NULL(e) (void)
    //#endif
#endif

#endif /* PLATFORM_FRAMEWORK_INC_UTILITY_H_ */

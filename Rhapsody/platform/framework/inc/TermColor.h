/**
 *  \brief     Class for VT100 Terminal definition.
 *  \details   This class contains a set of enumerations which set colour and attributes \n
 *             for VT100. Use \<stream\> << TermColor::\<attribute\>
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      14.06.2016
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef _TERMCOLOR_H_
#define _TERMCOLOR_H_

//#include <iostream>
#ifdef _GLIBCXX_IOSTREAM
#include <iomanip>
#endif
#include <cstdio>
#include <inttypes.h>
#include <cwchar>
#include <string>


namespace Platform
{
namespace BSP
{

/**
 *  \class TermColor inc/TermColor.h
 *  class with all colors and attribute for formatted VT100 output.\n
 *  Also, the << operator can be used to output common data types and to set \ref Attribute and \ref Color
 *  Class follows the singleton design pattern\n
 *
 */

#ifdef X
#undef X
#endif

#define LIST_OF_COLORS \
   X(black,         "\x1b[30m") \
   X(red,           "\x1b[31m") \
   X(green,         "\x1b[32m") \
   X(yellow,        "\x1b[33m") \
   X(blue,          "\x1b[34m") \
   X(magenta,       "\x1b[35m") \
   X(cyan,          "\x1b[36m") \
   X(white,         "\x1b[37m") \
   X(stdcol,        "\x1b[39m") \
   X(lightgray,     "\x1b[90m") \
   X(lightred,      "\x1b[91m") \
   X(lightgreen,    "\x1b[92m") \
   X(lightyellow,   "\x1b[93m") \
   X(lightblue,     "\x1b[94m") \
   X(lightmagenta,  "\x1b[95m") \
   X(lightcyan,     "\x1b[96m") \
   X(lightwhite,    "\x1b[97m")
/*!
 * \def LIST_OF_COLORS
 * defines all colors used in enum \ref Color and their escape sequences
 */



/*!
 * defines all colors used in enum \ref Attribute and their escape sequences
 */
#define LIST_OF_ATTRIBUTES \
   X(all,              "\x1b[0m")  \
   X(boldOn,           "\x1b[1m")  \
   X(italicOn,         "\x1b[3m")  \
   X(underlineOn,      "\x1b[4m")  \
   X(blinkOn,          "\x1b[5m")  \
   X(inverseOn,        "\x1b[7m")  \
   X(strikethroughOn,  "\x1b[9m")  \
   X(boldOff,          "\x1b[22m") \
   X(italicOff,        "\x1b[23m") \
   X(underlineOff,     "\x1b[24m") \
   X(blinkOff,         "\x1b[25m") \
   X(inverseOff,       "\x1b[27m") \
   X(strikethroughOff, "\x1b[29m") \
   X(cls,              "\x1b[2J")  \
   X(home,             "\x1b[H")


class TermColor
{
public:

    /// Font colors
#define X(enumname, string)   enumname,
  enum Color
  {
    LIST_OF_COLORS
  };
#undef X

#define X(attname, string)   attname,
  enum Attribute
  {
     LIST_OF_ATTRIBUTES
  };
#undef X

  /*!
   * \enum Color
   * Enumeration for all colors used in systems.\n
   * The enumeration values can be used to change color of serial output.
   */

  /*! \enum Attribute
   * Enumeration for all text attributes used in systems.\n
   * The enumeration values can be used to change attribute of serial output.
   */


    /// Just for compatibly with std::ostream
    enum Dummy
    {
        dfill,               ///< used for compatibly with std::setfill()
        dwidth               ///< used for compatibly with std::setwidth()
    };

    /**
     * Sets font color
     * @param [in]  c  \ref Color value of color
     */
    void setCol(Color c) const
    {
#ifdef _GLIBCXX_IOSTREAM
     // std::cout << std::flush;
      std::cout << colors[ c ];
#else
      fputs(colors[ c ], stdout);
#endif
    }

    /**
     * Sets font attribute
     * @param [in]  c  \ref Attribute value of attribute
     */
    void setAtt(Attribute c) const
    {
#ifdef _GLIBCXX_IOSTREAM
        // std::cout << std::flush;
      std::cout << attributes[ c ];
#else
      fputs(attributes[ c ], stdout);
#endif

    }

#ifndef _GLIBCXX_IOSTREAM
    /*!
     * \brief sets attribute of VT100 Terminal
     * \param [in] c \ref Attribute of VT100 Terminal
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(Attribute c) const
    {
        setAtt(c);
        return *this;
    }

    /*!
     * \brief sets color of VT100 Terminal
     * \param [in] c \ref Color of VT100 Terminal
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(Color c) const
    {
        setCol(c);
        return *this;
    }

    /*!
     * \brief Just for compatibly, allows calls like:  cout << setw() << ....
     * as setw() returns \ref Dummy object which is put into stream
     * \param [in] c \ref Dummy object
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(Dummy c) const
    {
        (void)c;   // to prevent warning;
        return *this;
    }


    /*!
     * \brief prints char
     * \param [in] c char to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(char c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%" PRIu32 "c",m_width);
        printf(ps,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints C string
     * \param [in] s C string to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(const char* s) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%" PRIu32 "s",m_width);
        printf(ps,s);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints wchar_t
     * \warning This call requires at least 1 kiByte stack due to lib implementation!!!
     * \param [in] c wchar_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(wchar_t c) const
    {
        wprintf(L"%lc",c);
        return *this;
    }

    /*!
     * \brief prints C string of wchar_t
     * \warning This call requires at least 1 kiByte stack due to lib implementation!!!
     * \param [in] s C string to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(const wchar_t* s) const
    {
        wprintf(L"%ls",s);
        return *this;
    }


    /*!
     * \brief prints std:string
     * \param [in] s string to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(const std::string& s) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 "c",m_flags,m_width);
        printf(ps,s.c_str());
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints uint8_t
     * \param [in] c uint8_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(uint8_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIu8,m_flags,m_width);
        printf(ps,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints int8_t
     * \param [in] c int8_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(int8_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIi8,m_flags,m_width);
        printf(ps,c);
        // m_width = 0;
        return *this;
    }

    /*!
     * \brief prints uint16_t
     * \param [in] c uint16_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(uint16_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIu16,m_flags,m_width);
        printf(ps,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints int16_t
     * \param [in] c int16_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(int16_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIi16,m_flags,m_width);
        printf(ps,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints uint32_t
     * \param [in] c uint32_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(uint32_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIu32,m_flags,m_width);
        printf(ps,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints int32_t
     * \param [in] c int32_t to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(int32_t c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%s%" PRIu32 PRIi32,m_flags,m_width);
        printf("%" PRIi32,c);
        m_width = 0;
        return *this;
    }

    /*!
     * \brief prints pointer
     * \param [in] c pointer (address) to print
     * \return Reference to \ref TermColor object
     */
    const TermColor& operator<<(const void* c) const
    {
        char ps[20];
        snprintf(ps,sizeof(ps),"%%%" PRIu32 "p",m_width);
        printf(ps, c);
        m_width = 0;
        return *this;
    }
#endif // #ifndef _GLIBCXX_IOSTREAM

    /**
     * \brief gets singleton instances of TermColor object.
     * \return reference to singleton
     */
    static TermColor & getInstance()
    {
        static TermColor inst;
        return  inst;
    };

    /**
     * \brief gets fill character
     * \return fill character
     */
    char fill() const {return m_fill;}

    /**
     * \brief sets fill character
     * \param [in] fillch new fill character
     * \return previous fill character
     */
    char fill(char fillch)
    {
        char old = m_fill;
        m_fill = fillch;
        setFlags();
        return old;
    }


    /**
     * \brief gets width of output
     * \returns width of output
     */
    uint32_t width() const {return m_width;}
    /**
     * \brief sets width of output
     * \param [in] wide new width
     * \returns previous width
     */

    uint32_t width(uint32_t wide) {uint32_t old = m_width; m_width = wide; return old;}

    static const char endl = '\n';   ///< line feed character
 private:
    TermColor() :
        m_width(0),
        m_fill(' '),
        m_isHex(false),
        m_isOctal(false),
        m_isLeft(false),
        m_forceSign(false)
     { m_flags[0] = '\0';};
    ~TermColor() {setCol(stdcol);}

    void setFlags()
    {
        uint32_t i = 0;
        if(m_isLeft)      m_flags[i++] = '-';
        if(m_forceSign)   m_flags[i++] = '+';
        if(m_fill == '0') m_flags[i++] = '0';
        m_flags[i] = '\0';
    }

    /// Array of escape sequences for colors, see VT100 specification
#define X(enumname, string)   string,
    /*!
     * Escape sequences for colors
     */
    const char* colors[lightwhite+1] =
    {
        LIST_OF_COLORS
    };
#undef X

#define X(attname, string)   string,
    /*!
     * \var TermColor::attributes Escape sequences for attributes
     */
    const char* attributes[home+1] =
    {
        LIST_OF_ATTRIBUTES
    };
#undef X

    mutable uint32_t m_width;
    char             m_fill;
    char             m_flags[5];
    bool             m_isHex;
    bool             m_isOctal;
    bool             m_isLeft;
    bool             m_forceSign;
};


/**
 * \brief inline function to set width in output stream\n
 * can be used like std::setw() manipulator
 * \param[in] n new width
 * \returns \ref Dummy object, therefore function can be used as manipulator
 */
inline
TermColor::Dummy setw(int n)
{
    TermColor::getInstance().width(n);
    return TermColor::dwidth;
}


/**
 * \brief inline function to set fill character in output stream\n
 * can be used like std::setfill() manipulator
 * \param[in] c new fill character
 * \returns \ref Dummy object, therefore function can be used as manipulator
 */

inline
TermColor::Dummy setfill(char c)
{
    TermColor::getInstance().fill(c);
    return TermColor::dfill;
}


#ifdef _GLIBCXX_IOSTREAM
/**
 * inline operator function to set color in output stream\n
 * sets new font color
 * @param [in] o reference to output stream
 * @param [in] c \ref Color value
 * @return reference to output stream
 */
inline
std::ostream &operator<<(std::ostream& o, TermColor::Color c)
{
   TermColor::getInstance().setCol(c);
   return o;
}

/**
 * inline operator function to set attribute in output stream\n
 * sets new font attribute
 * @param [in] o reference to output stream
 * @param [in] c \ref Attribute value
 * @return reference to output stream
 */

inline
std::ostream &operator<<(std::ostream& o, TermColor::Attribute c)
{
    TermColor::getInstance().setAtt(c);
    return o;
}
#endif

extern TermColor& cout; ///< Reference to TermColor object, can be used as output stream, usage similar to std::cout
}   // namespace Platform
}   // namespace BSP

#endif  // _TERMCOLOR_H_

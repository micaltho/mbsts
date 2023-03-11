/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/String/OMString/OMString.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMString_H
#define OMString_H

#include "RXF_Types.h"
//#[ ignore
// Global string functions that complete the OMString class definition
//#]


/* @MISRA_OMString=OFF XD-0001: No MISRA Check for OMString. */
class OMString;

typedef OMString RhpString;
// Greater than or equal to compare C string to an OMString
// Argument const RXF::char_t* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
bool operator>=(const RXF::char_t* c1, const OMString& s2);

// Greater than compare C string to an OMString
// Argument const RXF::char_t* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
bool operator>(const RXF::char_t* c1, const OMString& s2);

// Equal to compare C string to an OMString
// Argument const RXF::char_t* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
bool operator==(const RXF::char_t* c1, const OMString& s2);

// Less than or equal to compare C string to an OMString
// Argument const RXF::char_t* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
bool operator<=(const RXF::char_t* c1, const OMString& s2);

// Less than compare C string to an OMString
// Argument const RXF::char_t* c1 :
// The C string source
// Argument const OMString& s2 :
// The string to compare with
bool operator<(const RXF::char_t* c1, const OMString& s2);

// Add stings
// Argument const OMString& s1 :
// A string to add
// Argument const OMString& s2 :
// A string to add
OMString operator+(const OMString& s1, const OMString& s2);

// Add stings
// Argument const OMString& s1 :
// A string to add
// Argument const RXF::char_t* s2 :
// A string to add
OMString operator+(const OMString& s1, const RXF::char_t* s2);

// Add stings
// Argument const RXF::char_t* s1 :
// The C string
// Argument const OMString& s2 :
// The OMString
OMString operator+(const RXF::char_t* s1, const OMString& s2);

// not equal test
// Argument const RXF::char_t* c1 :
// The source
// Argument const OMString& s2 :
// Compared string
bool operator!=(const RXF::char_t* c1, const OMString& s2);

// Add a sting and a character
// Argument const OMString& str :
// A string to add
// Argument const RXF::char_t ch :
// The character
OMString operator+(const OMString& str, const RXF::char_t ch);

// A string class, supports the same API as CString.
class OMString {
public :

    // Initialize a string based on another string
    // Argument const OMString& s1 :
    // The source string
    OMString(const OMString& s1);
    
    // Initialize a string based on a single character
    // Argument const RXF::char_t ch :
    // The character
    OMString(const RXF::char_t ch);
    
    // Initialize a string based on another string (C style)
    // Argument const RXF::char_t* st :
    // The C string
    OMString(const RXF::char_t* st);
    
    // Initialize a string based on an unsigned integer value.
    // Internally uses the non reentrant itoa operation.
    OMString(const std::uint32_t num);
    
    // Initialize a string based on an unsigned integer value.
    // A length argument can be specified.
    // If the length is smaller than needed for the given integer, the result string will be cut off .
    // If it is longer than the integer value requires, it is filled with leading zeros.
    // Internally uses the non reentrant itoa operation.
    OMString(const std::uint32_t num, const std::uint8_t len);
    
    // Initialize an empty string
    OMString(void);
    
    // Cleanup
    ~OMString(void);

private :

    void initWithCharString(const RXF::char_t* const st);

public :

    // empty the string
    void Empty(void);
    
    // get a character at a given position
    // Argument const std::int32_t ind :
    // The index
    RXF::char_t GetAt(const std::int32_t ind);
    
    // get the string buffer
    // Argument int /**/ :
    // dummy
    char* GetBuffer(int /**/) const;
    
    // get the string buffer, readjusting its size.
    // Argument const std::int32_t newBufferSize :
    // The new buffer minimal size
    RXF::char_t* GetBuffer(const std::int32_t newBufferSize);
    
    // check if string is empty
    bool IsEmpty(void) const;
    
    // Release buffer sets the count value. It must be called before any use of string, if GetBuffer was used for direct change.
    // Argument const std::int32_t nNewLength = -1 :
    // The new string count. It can be called without argument, if buffer string ends with null character.
    void ReleaseBuffer(const std::int32_t nNewLength = -1);
    
    // set a character at a given position
    // Argument const std::int32_t ind :
    // The index
    // Argument const RXF::char_t ch :
    // The character
    void SetAt(const std::int32_t ind, const RXF::char_t ch);
    
    // cast operator
    operator const char*(void);
    
    // not equal test with a C string
    // Argument const RXF::char_t* c2 :
    // The C string
    bool operator!=(const RXF::char_t* c2) const;
    
    // not equal test with a string
    // Argument const OMString& s2 :
    // The string
    bool operator!=(const OMString& s2) const;
    
    // Add a C style string to the end of this string
    // Argument const RXF::char_t* st :
    // The string
    const OMString& operator+=(const RXF::char_t* st);
    
    // Add a character to the end of this string
    // Argument const RXF::char_t ch :
    // The character
    const OMString& operator+=(const RXF::char_t ch);
    
    // Add a string to the end of this string
    // Argument const OMString st :
    // The string
    const OMString& operator+=(const OMString st);
    
    // Less than test
    // Argument const RXF::char_t* c2 :
    // The context string
    bool operator<(const RXF::char_t* c2) const;
    
    // Less than test
    // Argument const OMString& s2 :
    // The context
    bool operator<(const OMString& s2) const;
    
    // Less than or equal to test
    // Argument const RXF::char_t* c2 :
    // The context
    bool operator<=(const RXF::char_t* c2) const;
    
    // Less than or equal to test
    // Argument const OMString& s2 :
    // The context
    bool operator<=(const OMString& s2) const;
    
    // Assign the specified string as the value of this string
    // Argument const RXF::char_t* st :
    // The context
    const OMString& operator=(const RXF::char_t* st);
    
    // Assign the specified character as the value of this string
    // Argument const RXF::char_t ch :
    // The context
    const OMString& operator=(const RXF::char_t ch);
    
    // Assign the specified string as the value of this string
    // Argument const OMString& st :
    // The context
    const OMString& operator=(const OMString& st);
    
    // Compare this string with the specified string
    // Argument const RXF::char_t* c2 :
    // The context
    bool operator==(const RXF::char_t* c2) const;
    
    // Compare this string with the specified string
    // Argument const OMString& s2 :
    // The context
    bool operator==(const OMString& s2) const;
    
    // Greater than test
    // Argument const RXF::char_t* c2 :
    // The context
    bool operator>(const RXF::char_t* c2) const;
    
    // Greater than test
    // Argument const OMString& s2 :
    // The context
    bool operator>(const OMString& s2) const;
    
    // Greater than or equal to test
    // Argument const RXF::char_t* c2 :
    // The context
    bool operator>=(const RXF::char_t* c2) const;
    
    // Greater than or equal to test
    // Argument const OMString& s2 :
    // The context
    bool operator>=(const OMString& s2) const;
    
    // return the character at the given position
    // Argument const std::int32_t ind :
    // The index
    RXF::char_t operator[](const std::int32_t ind) const;
    
    // give string a new larger size
    // and copy contents to it.
    // Argument const std::int32_t newSize :
    // The new buffer minimal size
    void resetSize(const std::int32_t newSize);

private :

    // allocate the string buffer
    // Argument const std::int32_t newSize = defaultBlock :
    // The new buffer minimal size
    void setSize(const std::int32_t newSize = defaultBlock);

public :

    std::int32_t GetLength(void) const;
    
    std::int32_t getDefaultBlock(void);
    
    std::int32_t getSize(void) const;
    
    RXF::char_t* getStr(void) const;

private :

    // No case compare
    // Argument const RXF::char_t* const s1 :
    // The source string
    // Argument const RXF::char_t* const s2 :
    // The string to compare with
    static std::int32_t CompareNoCase_(const RXF::char_t* const s1, const RXF::char_t* const s2);

public :

    // No case compare
    // Argument const RXF::char_t* const s2 :
    // The string to compare with
    std::int32_t CompareNoCase(const RXF::char_t* const s2) const;
    
    // No case compare
    // Argument const OMString& s2 :
    // The string to compare with
    std::int32_t CompareNoCase(const OMString& s2) const;
    
    static std::int32_t toupper(const std::int32_t character);
    
    // Unsigned integer to zero terminated character string conversion.
    // This operation is not reentrant, as it uses a static character array "aString".
    RXF::char_t* itoa(const std::uint32_t num);
    
    // Unsigned integer to zero terminated character string conversion.
    // A length argument can be specified.
    // If the length is smaller than needed for the given integer, the result string will be cut off .
    // If it is longer than the integer value requires, it is filled with leading zeros.
    // This operation is not reentrant, as it uses a static character array "aString".
    RXF::char_t* itoa(const std::uint32_t num, std::uint8_t len);
    
    // String to unsigned integer conversion.
    // It does not check for valid digit characters inside the string.
    std::uint32_t atoi(void);
    
    ////    Attributes    ////

private :

    // How many chars we currently have (without the '\0')
    std::int32_t count;
    
    // the string default size
    // need to be declared before used (in this file) to avoid compilation issues in some compilers
    static std::int32_t defaultBlock;
    
    // The current allocated memory
    std::int32_t size;
    
    // Pointer to actual string
    RXF::char_t* str;
};

/* @MISRA_OMString=ON (end of XD-0001) */

#endif
/*********************************************************************
	File Path	: ../Source/String/OMString/OMString.h
*********************************************************************/

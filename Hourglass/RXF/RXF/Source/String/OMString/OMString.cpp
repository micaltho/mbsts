/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/String/OMString/OMString.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Config.h"
#include <string.h>
#include "OMString.h"

/* @MISRA_OMString=OFF XD-0001: No MISRA Check for OMString. */

bool operator>=(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1,s2.GetBuffer(0)) >= 0);
}

bool operator>(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1,s2.GetBuffer(0)) > 0);
}

bool operator==(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1,s2.GetBuffer(0)) == 0);
}

bool operator<=(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1,s2.GetBuffer(0)) <= 0);
}

bool operator<(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1,s2.GetBuffer(0)) < 0);
}

OMString operator+(const OMString& s1, const OMString& s2)
{
    OMString res(s1);
    res += s2;
    return res; 
}

OMString operator+(const OMString& s1, const RXF::char_t* s2)
{
    OMString res(s1);
    res += s2;
    return res; 
}

OMString operator+(const RXF::char_t* s1, const OMString& s2)
{
    OMString res(s1);
    res += s2;
    return res;
}

bool operator!=(const RXF::char_t* c1, const OMString& s2)
{
    return (strcmp(c1, s2.GetBuffer(0)) != 0);
}

OMString operator+(const OMString& str, const RXF::char_t ch)
{
    OMString res(str);
    res += ch;
    return res;
}

std::int32_t OMString::defaultBlock = 256;

OMString::OMString(const OMString& s1) : count(0), size(0), str(0)
{
    count = s1.count;
    setSize( count + 1 );
    if ( count > 0 ){ 
    	memcpy( str, s1.str, (unsigned int) count + 1 );
    } 
    else { 
    	str[count] = '\0'; 
    }
}

OMString::OMString(const RXF::char_t ch) : count(0), size(0), str(0)
{
    count = 1;
    setSize(count + 1);
    str[0] = ch;
    str[count] = '\0';
}

OMString::OMString(const RXF::char_t* st) : count(0), size(0), str(0)
{
    initWithCharString( st );
}

OMString::OMString(const std::uint32_t num) : count(0), size(0), str(0)
{
    initWithCharString( itoa( num ) );
}

OMString::OMString(const std::uint32_t num, const std::uint8_t len) : count(0), size(0), str(0)
{
    initWithCharString( itoa( num, len ) );
}

OMString::OMString(void) : count(0), size(0), str(0)
{
    setSize(1);
    str[0] = '\0';
}

OMString::~OMString(void)
{
    if (size > 0)
    {
    	delete str;
    }
    str = nullptr;
    size = 0;
    count = 0;
}

void OMString::initWithCharString(const RXF::char_t* const st)
{
    if (st != 0) {
    	count = static_cast<int>(strlen(st));
    	setSize(count + 1);
    	if (count > 0) { 
    		memcpy(str, st, strlen(st) + 1);
    	} 
    	else { 
    		str[count] = '\0'; 
    	} 
    }
    else{
    	setSize(count + 1);
    	str[count]='\0';
    }
}

void OMString::Empty(void)
{
    if (count > 0)
    {
    	count = 0;
    	// lint fails to identify the correlation between count and str
    	str[count]='\0';  //lint !e613
    }
}

RXF::char_t OMString::GetAt(const std::int32_t ind)
{
    char retVal = '\0';
    if (ind > -1 && ind < count)
    {
    	retVal = str[ind];
    }           
    return retVal;
}

char* OMString::GetBuffer(int /**/) const
{
    return str;
}

RXF::char_t* OMString::GetBuffer(const std::int32_t newBufferSize)
{
    resetSize(newBufferSize);
    return str;
}

bool OMString::IsEmpty(void) const
{
    return count == 0; 
}

void OMString::ReleaseBuffer(const std::int32_t nNewLength)
{
    if (nNewLength == -1)
    {
    	count = static_cast<int>(strlen(str));
    }
    else
    {
    	if (nNewLength <= size)
    	{
    		count = nNewLength;
    		if (count < size)
    		{
    			str[count] = '\0';
    		}
    	}
    }
}

void OMString::SetAt(const std::int32_t ind, const RXF::char_t ch)
{
    if (ind < count)
    {
    	// lint fails to identify the correlation between count and str
    	str[ind] = ch;	//lint !e613
    }
}

OMString::operator const char*(void)
{
    return str;
}

bool OMString::operator!=(const RXF::char_t* c2) const
{
    return (strcmp(str, c2) != 0);  //lint !e668 (OMString::str is never nullptr)
}

bool OMString::operator!=(const OMString& s2) const
{
    return (strcmp(str, s2.str) != 0); //lint !e668 (OMString::str is never nullptr)
}

const OMString& OMString::operator+=(const RXF::char_t* st)
{
    if(st){
    	int newCount = count + static_cast<int>(strlen(st));
    	resetSize(newCount + 1);
    	if(str){
    		memcpy(str + count, st, strlen(st) + 1);
    		count = newCount;
    	}
    }
    return *this;
}

const OMString& OMString::operator+=(const RXF::char_t ch)
{
    ++count;
    resetSize(count + 1);
    if(str) {
    	str[count-1] = ch;
    	str[count] = '\0';
    }
    return *this;
}

const OMString& OMString::operator+=(const OMString st)
{
    int newCount = count + st.count;
    resetSize(newCount + 1);
    if (str) {
    	memcpy(str + count, st.str, (unsigned int) st.count + 1);
    	count = newCount;
    }
    return *this;
}

bool OMString::operator<(const RXF::char_t* c2) const
{
    bool smaller = false;
    if (c2 != 0) {
    	smaller = (strcmp(str,c2) < 0); //lint !e668 (str is never nullptr)
    }
    return smaller;
}

bool OMString::operator<(const OMString& s2) const
{
    return (strcmp(str, s2.str) < 0); //lint !e668 (OMString::str is never nullptr)
}

bool OMString::operator<=(const RXF::char_t* c2) const
{
    bool res = false;
    if (c2 != 0) {
    	res = (strcmp(str, c2) <= 0); //lint !e668 (str is never nullptr)
    }
    return res;
}

bool OMString::operator<=(const OMString& s2) const
{
    return (strcmp(str, s2.str) <= 0);	//lint !e668 (OMString::str is never nullptr)
}

const OMString& OMString::operator=(const RXF::char_t* st)
{
    if (st) {
    	count = static_cast<int>(strlen(st));
    	resetSize(count + 1);
    	if (str) {
    		memcpy(str, st, strlen(st) + 1);
    	}
    }
    return *this;
}

//lint -save -e1539 (the size doesn't change only the data)
const OMString& OMString::operator=(const RXF::char_t ch)
{
    count = 1;
    if (str) {
    	str[0] = ch;
    	str[count] = '\0';
    }
    return *this;
}

//lint -restore

const OMString& OMString::operator=(const OMString& st)
{
    if(str != st.str) {
    	count = st.count;
    	resetSize(count + 1);
    	if (str) {
    		memcpy(str, st.str, static_cast<unsigned int>(count) + 1);
    	}
    }
    return *this;
}

bool OMString::operator==(const RXF::char_t* c2) const
{
    bool res = false;
    if (c2 != 0) {
    	res = (strcmp(str, c2) == 0); //lint !e668 (str is never nullptr)
    }
    return res;
}

bool OMString::operator==(const OMString& s2) const
{
    return (strcmp(str, s2.str) == 0); //lint !e668 (str is never nullptr)
}

bool OMString::operator>(const RXF::char_t* c2) const
{
    bool res = true;
    if (c2 != 0) {
    	res = (strcmp(str, c2) > 0); //lint !e668 (str is never nullptr)
    }
    return res;
}

bool OMString::operator>(const OMString& s2) const
{
    return (strcmp(str, s2.str) > 0);	//lint !e668 (str is never nullptr)
}

bool OMString::operator>=(const RXF::char_t* c2) const
{
    bool res = true;
    if (c2 != 0) {
    	res = (strcmp(str, c2) >= 0);	//lint !e668 (str is never nullptr)
    }
    return res;
}

bool OMString::operator>=(const OMString& s2) const
{
    return (strcmp(str, s2.str) >= 0);	//lint !e668 (str is never nullptr)
}

RXF::char_t OMString::operator[](const std::int32_t ind) const
{
    return str[ind];
}

void OMString::resetSize(const std::int32_t newSize)
{
    // Do we need to allocate new memory
    if (size < newSize) {
    	// retain a pointer to the actual data
    	char* oldStr = str;
    	// allocate the new memory
    	int oldSize = size;
    	setSize(newSize);
    	// copy the actual data to the new location
    	if (str && oldStr) {
    		memcpy(str,oldStr, (unsigned int)oldSize);
    	}
    	// free memory used by the old location    
    	delete oldStr;
    }
}

void OMString::setSize(const std::int32_t newSize)
{
    
    // Round size up to the nearest stringBlock
    size = (newSize / defaultBlock) * defaultBlock;
    if (newSize > size) {
    	size += defaultBlock;
    }
    // Actually allocate the memory    
    str = new char[ size ];
    
}

std::int32_t OMString::GetLength(void) const
{
    return count;
}

std::int32_t OMString::getDefaultBlock(void)
{
    return defaultBlock;
}

std::int32_t OMString::getSize(void) const
{
    return size;
}

RXF::char_t* OMString::getStr(void) const
{
    return str;
}

std::int32_t OMString::CompareNoCase_(const RXF::char_t* const s1, const RXF::char_t* const s2)
{
    // res = 3 - unknown
    int res = 3;
    if ((s1 != 0) && (s2 != 0)) {
    	std::int32_t index = 0;
    	while ( res == 3 ) {
    		RXF::char_t d1 = (RXF::char_t)toupper(s1[index]);
    		RXF::char_t d2 = (RXF::char_t)toupper(s2[index]);
    		if (d1 < d2) {
    			res = -1;
    		}
    		else if (d1 > d2) {
    			res = 1;
    		}
    		else if (d1 == '\0') {
    			res = 0;
    		}
    		index++;
    	}
    }
    return res;
}

std::int32_t OMString::CompareNoCase(const RXF::char_t* const s2) const
{
    return CompareNoCase_(str,s2);
}

std::int32_t OMString::CompareNoCase(const OMString& s2) const
{
    return CompareNoCase_(str, s2.str);
}

std::int32_t OMString::toupper(const std::int32_t character)
{
    std::int32_t res = character;
    if ((character >= 97) && (character <= 122)) {
    	res = (character - 32);
    }
    return res;
}

RXF::char_t* OMString::itoa(const std::uint32_t num)
{
    RXF::char_t 			buf[12] = {0};
    static RXF::char_t	aString[12] = {0};
    std::uint32_t		n = num;
    
    std::uint8_t counter = 0U;  
    
    if (n==0)
    {
    	buf[counter++] = '0';
    }
    
    for(; n ; n /= 10)
    {
        buf[counter++] = (RXF::char_t)('0' + (n % 10));
    }
    
    for (int i = 0; i<counter; ++i)
    {
    	aString[i] = buf[counter - i - 1];
    }
    aString[counter] = '\0';
    
    return aString;
}

RXF::char_t* OMString::itoa(const std::uint32_t num, std::uint8_t len)
{
    RXF::char_t          buf[12] = { 0 };
    static RXF::char_t   aString[12] = { 0 };
    std::uint32_t   n = num;
    std::uint8_t    counter = 0U;
    std::uint8_t    i;
    std::int8_t     j;
    
    if (len > 11U)
    {
    	// larger than the aString array, reducing to avoid array index out of bounds access.
    	len = 11U;
    }
    
    if (n == 0)
    {
    	buf[counter++] = '0';
    }
    
    for (; n; n /= 10U)
    {
    	buf[counter++] = (RXF::char_t)('0' + (n % 10U));
    }
    
    for (j = static_cast<std::int8_t>(len) - 1 - static_cast<std::int8_t>(counter); j >= 0; j--)
    {
    	aString[j] = '0';
    }
    j = static_cast<std::int8_t>(len - counter);
    for (i = 0U; i < counter; ++i)
    {
    	aString[i + j] = buf[len - i - j - 1];
    }
    aString[len] = '\0';
    
    return aString;
}

std::uint32_t OMString::atoi(void)
{
    std::uint32_t res = 0U;
    RXF::char_t* myStr = this->getStr();
    
    for (std::uint8_t i = 0U; myStr[i] != '\0'; i++) 
    {
    	res = res*10+ myStr[i] - '0';
    }                           
    return(res);
}

/* @MISRA_OMString=ON (end of XD-0001) */

/*********************************************************************
	File Path	: ../Source/String/OMString/OMString.cpp
*********************************************************************/

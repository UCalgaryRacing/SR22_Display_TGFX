/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x46, 0x72, 0x6f, 0x6e, 0x74, 0x20, 0x42, 0x72, 0x61, 0x6b, 0x65, 0x3a, 0x20, 0x2, 0x56, 0x0, // @0 "Front Brake: <>V"
    0x46, 0x75, 0x65, 0x6c, 0x20, 0x50, 0x72, 0x65, 0x73, 0x3a, 0x20, 0x2, 0x62, 0x61, 0x72, 0x0, // @16 "Fuel Pres: <>bar"
    0x49, 0x67, 0x6e, 0x20, 0x41, 0x6e, 0x67, 0x6c, 0x65, 0x3a, 0x20, 0x2, 0x64, 0x65, 0x67, 0x0, // @32 "Ign Angle: <>deg"
    0x4c, 0x61, 0x6d, 0x62, 0x64, 0x61, 0x20, 0x43, 0x6f, 0x72, 0x72, 0x3a, 0x20, 0x2, 0x25, 0x0, // @48 "Lambda Corr: <>%"
    0x4f, 0x69, 0x6c, 0x20, 0x50, 0x72, 0x65, 0x73, 0x3a, 0x20, 0x2, 0x62, 0x61, 0x72, 0x0, // @64 "Oil Pres: <>bar"
    0x52, 0x65, 0x61, 0x72, 0x20, 0x42, 0x72, 0x61, 0x6b, 0x65, 0x3a, 0x20, 0x2, 0x56, 0x0, // @79 "Rear Brake: <>V"
    0x46, 0x75, 0x65, 0x6c, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x3a, 0x20, 0x2, 0x43, 0x0, // @94 "Fuel Temp: <>C"
    0x4f, 0x69, 0x6c, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x3a, 0x20, 0x2, 0x43, 0xa, 0x0, // @108 "Oil Temp: <>C\n"
    0x45, 0x43, 0x55, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x3a, 0x20, 0x2, 0x43, 0x0, // @122 "ECU Temp: <>C"
    0x4c, 0x6f, 0x6e, 0x67, 0x69, 0x74, 0x75, 0x64, 0x65, 0x3a, 0x20, 0x2, 0x0, // @135 "Longitude: <>"
    0x53, 0x70, 0x65, 0x65, 0x64, 0x3a, 0x20, 0x2, 0x6b, 0x6d, 0x2f, 0x68, 0x0, // @148 "Speed: <>km/h"
    0x41, 0x6c, 0x74, 0x69, 0x74, 0x75, 0x64, 0x65, 0x3a, 0x20, 0x2, 0x0, // @161 "Altitude: <>"
    0x42, 0x61, 0x74, 0x74, 0x65, 0x72, 0x79, 0x3a, 0x20, 0x2, 0x56, 0x0, // @173 "Battery: <>V"
    0x43, 0x6f, 0x6f, 0x6c, 0x61, 0x6e, 0x74, 0x3a, 0x20, 0x2, 0x43, 0x0, // @185 "Coolant: <>C"
    0x4c, 0x61, 0x74, 0x69, 0x74, 0x75, 0x64, 0x65, 0x3a, 0x20, 0x2, 0x0, // @197 "Latitude: <>"
    0x42, 0x61, 0x72, 0x6f, 0x3a, 0x20, 0x2, 0x6b, 0x50, 0x61, 0x0, // @209 "Baro: <>kPa"
    0x44, 0x77, 0x65, 0x6c, 0x6c, 0x3a, 0x20, 0x2, 0x6d, 0x73, 0x0, // @220 "Dwell: <>ms"
    0x46, 0x4c, 0x20, 0x50, 0x6f, 0x74, 0x3a, 0x20, 0x2, 0x56, 0x0, // @231 "FL Pot: <>V"
    0x46, 0x52, 0x20, 0x50, 0x6f, 0x74, 0x3a, 0x20, 0x2, 0x56, 0x0, // @242 "FR Pot: <>V"
    0x49, 0x4e, 0x4a, 0x50, 0x57, 0x3a, 0x20, 0x2, 0x6d, 0x73, 0x0, // @253 "INJPW: <>ms"
    0x52, 0x4c, 0x20, 0x50, 0x6f, 0x74, 0x3a, 0x20, 0x2, 0x56, 0x0, // @264 "RL Pot: <>V"
    0x52, 0x52, 0x20, 0x50, 0x6f, 0x74, 0x3a, 0x20, 0x2, 0x56, 0x0, // @275 "RR Pot: <>V"
    0x2, 0x3a, 0x2, 0x0, // @286 "<>:<>"
    0x4c, 0x61, 0x6d, 0x62, 0x64, 0x61, 0x3a, 0x20, 0x2, 0x0, // @290 "Lambda: <>"
    0x4d, 0x41, 0x50, 0x3a, 0x20, 0x2, 0x6b, 0x50, 0x61, 0x0, // @300 "MAP: <>kPa"
    0x45, 0x47, 0x54, 0x31, 0x3a, 0x20, 0x2, 0x43, 0x0, // @310 "EGT1: <>C"
    0x45, 0x47, 0x54, 0x32, 0x3a, 0x20, 0x2, 0x43, 0x0, // @319 "EGT2: <>C"
    0x45, 0x47, 0x54, 0x33, 0x3a, 0x20, 0x2, 0x43, 0x0, // @328 "EGT3: <>C"
    0x45, 0x47, 0x54, 0x34, 0x3a, 0x20, 0x2, 0x43, 0x0, // @337 "EGT4: <>C"
    0x47, 0x65, 0x61, 0x72, 0x3a, 0x20, 0x2, 0x0, // @346 "Gear: <>"
    0x49, 0x41, 0x54, 0x3a, 0x20, 0x2, 0x43, 0x0, // @354 "IAT: <>C"
    0x54, 0x50, 0x53, 0x3a, 0x20, 0x2, 0x25, 0x0, // @362 "TPS: <>%"
    0x43, 0x6f, 0x6f, 0x6c, 0x61, 0x6e, 0x74, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x0, // @370 "Coolant Temp"
    0x47, 0x50, 0x53, 0x3a, 0x20, 0x2, 0x0, // @383 "GPS: <>"
    0x4f, 0x69, 0x6c, 0x20, 0x50, 0x72, 0x65, 0x73, 0x73, 0x75, 0x72, 0x65, 0x0, // @390 "Oil Pressure"
    0x52, 0x50, 0x4d, 0x3a, 0x20, 0x2, 0x0, // @403 "RPM: <>"
    0x54, 0x54, 0x50, 0x4d, 0x53, 0x20, 0x54, 0x6f, 0x67, 0x67, 0x6c, 0x65, 0x0, // @410 "TTPMS Toggle"
    0x30, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0, // @423 "0.0000000"
    0x30, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0, // @433 "0.000000"
    0x4f, 0x69, 0x6c, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x0, // @442 "Oil Temp"
    0x42, 0x61, 0x74, 0x74, 0x65, 0x72, 0x79, 0x0, // @451 "Battery"
    0x30, 0x2e, 0x30, 0x30, 0x30, 0x30, 0x0, // @459 "0.0000"
    0x30, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x0, // @466 "00.000"
    0x30, 0x30, 0x2e, 0x30, 0x30, 0x0, // @473 "00.00"
    0x30, 0x30, 0x30, 0x2e, 0x30, 0x0 // @479 "000.0"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}

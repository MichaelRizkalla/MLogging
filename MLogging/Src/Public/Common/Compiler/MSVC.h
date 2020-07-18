#pragma once

#if !defined(_MSC_VER) || (_MSC_VER < 1910)
#error This is a MSVC17 or later compiler header
#endif

#define MLOGGING_EXPORT __declspec(dllexport)
#define MLOGGING_IMPORT __declspec(dllimport)


#ifndef MLOGGING_EXPORTS

#define MLOGGING_api MLOGGING_IMPORT
#define MLOGGING_class MLOGGING_IMPORT
#define MLOGGING_enum MLOGGING_IMPORT
#define MLOGGING_IMPORT_API 1

#else

#define MLOGGING_api MLOGGING_EXPORT
#define MLOGGING_class MLOGGING_EXPORT
#define MLOGGING_enum MLOGGING_EXPORT
#define MLOGGING_EXPORT_API 1
#endif

// --------------------------------------

#define MLOGGING(x) MLOGGING_##x

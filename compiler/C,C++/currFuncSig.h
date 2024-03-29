/**This file is specific to the C(++) compiler, not to its programming language.
 * Because it uses non-standard C(++) preprocessor macros.
 * So place it into file system directory ~"compiler/C,C++".*/
/**(c)from 2023:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Created 08.8.2023*/
/**file name can be as short as "currFnSig.h":
 * curr=CURRent: http://www.abbreviations.com/abbreviation/current
 * Fn=FuNction: http://www.allacronyms.com/function/abbreviated
 * Sig=SIGnature: http://www.abbreviations.com/abbreviation/signature */

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude: http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD: http://www.abbreviations.com/abbreviation/Guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * curr=CURRent: http://www.abbreviations.com/abbreviation/current
 * Fn/Fun/Func=FUNCtion: http://www.allacronyms.com/function/abbreviated
 * Sig=SIGnature: http://www.abbreviations.com/abbreviation/signature */\
 !defined TU_Bln361095compiler_C_andCpp_currFuncSig_h
  #define TU_Bln361095compiler_C_andCpp_currFuncSig_h

///see http://www.boost.org/doc/libs/1_46_1/boost/current_function.hpp

#ifdef __GNUC__///GNU C(++) compiler
/**Prog=PROGramming: http://www.allacronyms.com/programming/abbreviated
 * Lang=LANGuage: http://www.abbreviations.com/abbreviation/language
 * Use "progLang" prefix because "compiler" may also have other meanings:maker
 * of a compilation of sound etc.)*/
 #define TU_Bln361095progLangC_andCppCurrFnSig\
/**see http://gcc.gnu.org/onlinedocs/gcc/Function-Names.html ,
 * http://lists.llvm.org/pipermail/cfe-dev/2018-February/056766.html :
 *-C++: "__PRETTY_FUNCTION__" becomes in Extended Backus-Naur form
 *  (http://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form):
 * -function signature = 
 *   [>>return type<<
 *   " "] (no return type in constructors),
 *   {>>namespace name<< "::"},
 *   [>>class/struct name<<
 *    , template,
 *    "::"],
 *   >>function name<<
 *   "("
 *    {>>data type<<," "}[>>data type<<] (parameters list:no identifiers)
 *   ")",
 *   ["[with ">>template's typename<<" = ">>template's type<<<"]"];
 *    for example: "[with T = void]"
 * -template = ["<">>template's typename<<">"]
 *    (for example "template <typename T> class C")
 *-C: only the function name! */\
  __PRETTY_FUNCTION__
#endif
#ifdef _MSC_VER///Microsoft Visual Studio C(++) compiler("cl.exe")
/**Prog=PROGramming: http://www.allacronyms.com/programming/abbreviated
 * Lang=LANGuage: http://www.abbreviations.com/abbreviation/language
 * Use "progLang" prefix because "compiler" may also have other meanings:maker
 * of a compilation of sound etc.)*/
 #define TU_Bln361095progLangC_andCppCurrFnSig\
 /**see
http://social.msdn.microsoft.com/Forums/vstudio/de-DE/02c69018-a182-48b3-94d1-250252aa00a7/prettyfunction?forum=vclanguage
 * : "__FUNCSIG__" becomes in Extended Backus-Naur form
 *   (http://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form):
 * - [>>return type<<
 * - " "] (no return type in constructors)
 * - >>calling convention<<
 * - " "
 * - {>>namespace name<< "::"}
 * - [>>class name<< "::"]
 * - >>function name<<
 * - "("
 * - [>>parameter type<< {"," >>parameter type<<}]
 *   >>parameter type<< may be "class >>class name<<"?
 * - ")"
 * for example:"void __thiscall A::A::Func(class std::basic_ostream<char,struct
 *  std::char_traits<char> > &)" */\
  __FUNCSIG__
#endif

#endif///Include guard
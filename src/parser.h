#ifndef _LUA_PARSER_INCLUDE_H_
#define _LUA_PARSER_INCLUDE_H_


namespace lua {

    typedef enum {
        VVOID,	/* no value */
        VNIL,
        VTRUE,
        VFALSE,
        VK,		/* info = index of constant in `k' */
        VKNUM,	/* nval = numerical value */
        VLOCAL,	/* info = local register */
        VUPVAL,       /* info = index of upvalue in `upvalues' */
        VGLOBAL,	/* info = index of table; aux = index of global name in `k' */
        VINDEXED,	/* info = table register; aux = index register (or `k') */
        VJMP,		/* info = instruction pc */
        VRELOCABLE,	/* info = instruction pc */
        VNONRELOC,	/* info = result register */
        VCALL,	/* info = instruction pc */
        VVARARG	/* info = instruction pc */
    } expkind;

    class Parser {

    };
}


#endif  /* _LUA_PARSER_INCLUDE_H_ */

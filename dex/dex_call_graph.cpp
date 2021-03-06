/*@
XOC Release License

Copyright (c) 2013-2014, Alibaba Group, All rights reserved.

    compiler@aliexpress.com

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Su Zhenyu nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

author: Su Zhenyu
@*/
#include "libdex/DexFile.h"
#include "libdex/DexClass.h"
#include "libdex/DexProto.h"
#include "liropcode.h"
#include "lir.h"
#include "cominc.h"
#include "comopt.h"
#include "drAlloc.h"
#include "d2d_comm.h"
#include "dex.h"
#include "gra.h"
#include "dex_hook.h"
#include "dex_util.h"

static CHAR const* g_unimportant_func[] = {
    "Ljava/lang/StringBuilder;:()V:<init>",
};
static UINT g_unimportant_func_num =
    sizeof(g_unimportant_func) / sizeof(g_unimportant_func[0]);


DexCallGraph::DexCallGraph(UINT edge_hash, UINT vex_hash, RegionMgr * rumgr) :
        CallGraph(edge_hash, vex_hash, rumgr)
{
    ASSERT0(rumgr);
    SymTab * symtab = rumgr->get_sym_tab();
    for (UINT i = 0; i < g_unimportant_func_num; i++) {
        SYM const* sym = symtab->add(g_unimportant_func[i]);
        m_unimportant_symtab.append(sym);
    }
}


bool DexCallGraph::is_unimportant(SYM const* sym) const
{
    return m_unimportant_symtab.find(sym);
}

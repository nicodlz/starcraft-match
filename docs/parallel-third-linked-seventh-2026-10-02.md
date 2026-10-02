# Third-session seventh reviewed linked C lot — 2026-10-02

Four independently authored whole C functions add **538 exact original bytes**, following main tip `23ea13a`. Independent reviewers recompile copied projects and review complete boundaries, callers, ABI, dependencies and C domains. The coordinator separately recompiles final public paths.

Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Function | Original / linked bytes |
| --- | ---: |
| [004A5E40](functions/004A5E40.md) | 44 / 44 |
| [004DBD20](functions/004DBD20.md) | 60 / 60 |
| [00456B00](functions/00456B00.md) | 63 / 63 |
| [004E0200](functions/004E0200.md) | 371 / 371 |

The 371-byte routine uses native `_alloca` compiler generation. Its sole genuine undefined code relocation targets the original 61-byte stack-probe helper, reviewed for EAX count, ESP adjustment and register preservation. No source-defined helper, manual ABI shim or original-byte code is inserted; the helper implementation is uncounted. Eleven IAT mappings and the seven-stack-DWORD dynamic SetSecurityInfo call are reviewed. Zero or undersized API output and hooked-module behavior remain outside defined-C guarantees. Cleanup order remains CloseHandle then FreeSid. No security operation is executed.

The 44-byte entry is corroborated by an actual terminal JMP in a complete 264-byte caller, rather than trusting discovery CALL classification. It retains a DWORD reload between imports and the final BYTE clear. The 63-byte wrapper retains two independent pointer operations and their clears, including aliases and imported effects. The 60-byte search uses private ESI/EBX/EDI inputs, reloads its DWORD index after imports, and retains unsigned increment. Its runtime BSS pointer table and strings are not observable in the pinned file; no contents or API implementation are invented.

The aggregate is **443 exact functions / 27,800 bytes**, comprising **367 isolated zero-relocation COFF functions / 21,719 bytes** and **76 external-only standard-linked C functions / 6,081 bytes**. There are 450 source candidates, including four reviewed mismatches and three uncorroborated regions. Dependencies and contexts remain uncounted.

Validation passed final-path fresh coordinator compilation, local `make` with all 64 tests, complete `make proof` for all 443 exact entries, schema checks and the staged publication guard. Entire compiler contributions and every external relocation are checked, with nonrelocation bytes unchanged. No copied code, assembly, object editing, local helper rebinding, trimming, normalization or post-build patch is used. Private inputs and reports remain ignored; semantic/CFG metrics stay null where unmeasured. No original-process execution, full-program linking or playable game is claimed.

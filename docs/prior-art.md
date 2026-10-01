# Prior art and evidence boundaries

Research date: 2026-10-01. No third-party implementation was copied into this tree.
Source inspection clones stayed outside the repository, under `/tmp/`.

| Resource | What it provides | Evidence classification / limits |
| --- | --- | --- |
| [BWAPI](https://github.com/bwapi/bwapi), [setup](https://github.com/bwapi/bwapi/blob/main/README.md) | Interface into original 1.16.1; community-maintained structures and addresses | Community RE, not original source or proof of compiler output |
| [BWAPI CUnit](https://github.com/bwapi/bwapi/blob/main/bwapi/BWAPI/Source/BW/CUnit.h) | Packed 336-byte unit structure, explicit byte offsets and uncertain fields | Layout reference; only fields checked in a pinned original region count as locally verified |
| [BWAPI Offsets](https://github.com/bwapi/bwapi/blob/main/bwapi/BWAPI/Source/BW/Offsets.h) | Player array, game globals, hook addresses and typed memory views | Community mapping; no wholesale import |
| [BWAPI Constants](https://github.com/bwapi/bwapi/blob/main/bwapi/BWAPI/Source/BW/Constants.h), [OrderTypes](https://github.com/bwapi/bwapi/blob/main/bwapi/BWAPI/Source/BW/OrderTypes.h), [UnitStatusFlags](https://github.com/bwapi/bwapi/blob/main/bwapi/BWAPI/Source/BW/UnitStatusFlags.h) | Numeric order IDs, flags and game constants | Semantic annotations; not x86 opcode definitions or verified dispatch bounds |
| [BWAPI Broodwar.map](https://github.com/bwapi/bwapi/blob/d727fed68558c506163048ea889131d8cbb33915/Release_Binary/Starcraft/bwapi-data/data/Broodwar.map) | Public function names, addresses and lengths; leads for the four exact proof functions | Community symbol map; starts/sizes corroborated locally, original-name authenticity not established |
| [GPTP](https://github.com/BoomerangAide/GPTP), [CUnit implementation](https://github.com/BoomerangAide/GPTP/blob/master/GPTP/SCBW/structures/CUnit.cpp) | 1.16.1 hook addresses, register-based wrappers, comments distinguishing equivalent and similar routines | Community RE; hooks may replace behavior. Useful tiny-function leads |
| [OpenBW](https://github.com/OpenBW/openbw) | Alternative engine, simulation logic, file formats, replay behavior | Reimplementation reference. Its source shape, data layout and compiler output are not original evidence; no clean-room provenance audit performed |
| [OpenSnowstorm](https://github.com/awest813/OpenSnowstorm---Brood-War) | OpenBW-derived engine work and build/runtime integration | Reimplementation lineage, not a matching decompilation; no clean-room provenance audit performed |
| [EUDDB community mirror](https://gist.github.com/wdcqc/3b7b5a768bc05f99040b7c1ac885bb96) | Address catalog with types, descriptions and source links | Community memory map, useful cross-check; patch and provenance must be checked per entry |
| [Elias Bachaalany's StarCraft EUD presentation](https://files.bnetdocs.org/StarCraft_EUD_Emulator.pdf) | Blizzard engineer's account of reconstructing a close 1.16.1 build and mapping EUD addresses | Primary public historical testimony; VS 2003 identified, exact optimization switches not published there |
| [Microsoft PE/COFF specification](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format) | PE headers, RVAs, import/debug/resource directories and COFF layout | Format specification, not evidence of game semantics |
| [Ghidra](https://github.com/NationalSecurityAgency/ghidra) | Headless auto-analysis, function discovery, references and decompiler | Analysis engine; boundaries/prototypes/output can be wrong |

Locally inspected revisions: BWAPI `d727fed68558c506163048ea889131d8cbb33915`;
GPTP `ce321f0fa83174aee741b91f1b2eaec30300773e`. Links above follow their upstream
branches; use the recorded revisions when reproducing the initial inspection.

Specific leads:

- BWAPI lists player information at `0x0057EEE0` and game state at `0x0057F0F0`.
  Those globals have not been independently reconstructed or verified here.
- BWAPI's CUnit lists status at `0xDC`, lockdown at `0x117`, stasis at `0x119`,
  maelstrom at `0x124`. The original function at `0x004020B0` reads those offsets;
  timer/flag meanings remain community names attached to verified memory accesses.
- GPTP labels `0x004020B0` as an equivalent frozen-state check. Its location and
  four-condition predicate agree with our inspected specimen. Calling convention
  and bytes come from our binary, not GPTP's C++ method declaration.

Keep four evidence levels distinct in every task: **observed in the pinned binary**,
**community RE**, **reimplementation analogue**, **hypothesis**. A familiar symbol
name does not establish an original name, ABI, parameter type or function boundary.

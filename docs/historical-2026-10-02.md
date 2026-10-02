# Historical compiler — first matching lot

**134 whole C functions / 1,924 original bytes are exact**, up from 110 / 1,444.
The new lot adds **24 game functions / 480 bytes**. There are still 76 static
initializers / 836 bytes, counted separately from 58 other functions / 1,088 bytes.
New results include linked-list traversal, eight-entry counting loops, indexed
score calculations, full-width predicates and byte-only results.

All game observations concern the pinned Windows i386 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator reviewed complete boundaries, independent entry references,
caller or callback dispatcher contracts, access widths and register preservation,
then independently rebuilt each final public source. Complete isolated COFF
sections match without relocations, trimming, normalization, assembly copies,
embedded game bytes or output patches.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x00417E30](functions/00417E30.md) | canTextboxDlgAcceptEvents_CB | 24 / 24 | `msvc71-o2` |
| [0x00418010](functions/00418010.md) | isDlgVisible_CB | 27 / 27 | `msvc71-o2` |
| [0x004180A0](functions/004180A0.md) | DLG_prevEntry | 27 / 27 | `msvc71-o2` |
| [0x00428340](functions/00428340.md) | BTNSCOND_NoNydusExit | 23 / 23 | `msvc71-o2-frame` |
| [0x004288E0](functions/004288E0.md) | BTNSCOND_IsResearching | 24 / 24 | `msvc71-o2-frame` |
| [0x00428900](functions/00428900.md) | BTNSCOND_isUpgrading | 24 / 24 | `msvc71-o2-frame` |
| [0x00431F40](functions/00431F40.md) | AI_GetExpansionCount | 24 / 24 | `msvc71-o2` |
| [0x00432420](functions/00432420.md) | isUnitOwnedBy | 12 / 12 | `msvc71-o2` |
| [0x00436B10](functions/00436B10.md) | AI_getZergAirScore | 35 / 35 | `msvc71-o2-frame` |
| [0x00436EF0](functions/00436EF0.md) | loadedProc_UnitIsFirebat | 11 / 11 | `msvc71-o2` |
| [0x00440190](functions/00440190.md) | isDisabledAndOwnedProc | 28 / 28 | `msvc71-o2` |
| [0x00440220](functions/00440220.md) | AIUnitCanEnterBunkerProc | 24 / 24 | `msvc71-o2` |
| [0x004402A0](functions/004402A0.md) | compareUnitToUnitTypeProc | 10 / 10 | `msvc71-o2` |
| [0x00453DC0](functions/00453DC0.md) | UnitUpgradeRestrictionProc | 12 / 12 | `msvc71-o2` |
| [0x00454070](functions/00454070.md) | UltraliskUpgradeRestrictionProc | 25 / 25 | `msvc71-o2` |
| [0x00454090](functions/00454090.md) | VultureUpgradeRestrictionProc | 25 / 25 | `msvc71-o2` |
| [0x00475AD0](functions/00475AD0.md) | Unit_getGrndWeapon | 32 / 32 | `msvc71-o2` |
| [0x0047D170](functions/0047D170.md) | SendTextNull | 5 / 5 | `msvc71-o2` |
| [0x004872D0](functions/004872D0.md) | isValidPtr | 8 / 8 | `msvc71-o2` |
| [0x004872E0](functions/004872E0.md) | isNullPtr | 8 / 8 | `msvc71-o2` |
| [0x0048E9F0](functions/0048E9F0.md) | resetUnitAttackNotifyTimer | 10 / 10 | `msvc71-o2` |
| [0x0049DEF0](functions/0049DEF0.md) | cb_false | 5 / 5 | `msvc71-o2` |
| [0x004A8CD0](functions/004A8CD0.md) | CountFreeSlots | 28 / 28 | `msvc71-o2` |
| [0x004A8CF0](functions/004A8CF0.md) | getNumOpenSlots | 29 / 29 | `msvc71-o2` |

Names are community annotations, separate from the neutral source symbols.
Six bounded worker groups examined 36 leads. The remaining proposals failed
literal equality or require custom register arguments that this compiler cannot
express in pure C. Failed trials remain private. No success rate for the whole
game is inferred from this deliberately selected sample.

## Recorded historical compiler

The local compiler is Microsoft C/C++ **13.10.3077**, extracted privately from
Visual C++ Toolkit 2003. Microsoft described its free release in its
[announcement](https://devblogs.microsoft.com/buckh/download-the-vc-toolkit/).
The original Microsoft download is unavailable; the research container was
obtained from a [public university mirror](https://www.lysator.liu.se/~andro/exjobb/extras-win32/VCToolkitSetup.exe).
Installer SHA-256: `c040f6ffbc2259426dd523b7561575fe1704b58bc37092fbfe27b64aefc449f6`.
CL SHA-256: `2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`.

Container digest and signature mathematics were checked separately from current
trust. The embedded historical root matches Microsoft's published
[CCADB root identity](https://ccadb.my.salesforce-sites.com/microsoft/includedcacertificatereportformsft).
The certificate signatures and dates at the declared 2004 signing time were
checked; current standard trust verification fails, the root is disabled, and
historical revocation and TSA signature validation remain unverified. This is
not a claim of current certificate trust or proof of the original compiler build.
Installer, compiler, DLLs, runner and extraction/signature reports stay private.

The [wibo 1.2.0 release](https://github.com/decompals/wibo/releases/tag/1.2.0)
runner SHA-256 is `2575d3b0a2f408b2c2b0850db56f1af5d005a138394a6774eba77b6708ecc304`,
matching the official release asset digest. It runs only the compiler here.
The adapter records hashes of compiler components, runner and adapter, verifies
the compiler version and rejects ignored options. It clears implicit compiler
flags/include variables and publishes only a successful, unchanged compiler object.

`msvc71-o2` uses `/nologo /O2 /Oy /Gy /Zl /G6`;
`msvc71-o2-frame` disables frame omission with `/Oy-`. The unsupported `/GS-`
switch is rejected. Genuine fastcall and stack conventions are represented in C;
custom EAX/EBX/ESI/EDI argument contracts are deferred when not representable.
Matches do not establish a complete original compiler configuration.

## Validation and portable operation

`make proof` freshly rebuilt all **134 exact expectations / 1,924 bytes**.
`make` compiled all **156 candidates** and passed **20 tests**, including the
real-input proof regression and deliberate source mutation. Eleven new portable
synthetic tests cover the adapter and its evidence/fallback rules without any
Microsoft or game binaries. A source-only checkout without the original or private
toolchain builds all candidates; its real-input regression is skipped.

Only `build-all` may use an explicitly marked Clang source-compilation fallback
when the default historical toolchain is absent. A bad explicit configuration
fails. Individual builds, matches and proof verification require the recorded
compiler and cannot use that fallback. Component changes invalidate match evidence.
No game execution, whole-program linking or original differential execution was
performed; unavailable semantic and similarity metrics remain null.

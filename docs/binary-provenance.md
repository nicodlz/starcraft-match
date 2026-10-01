# Local executable provenance

Retrieved 2026-10-01 at the user's explicit request. The [SSCAIT tutorial](https://www.sscaitournament.com/index.php?action=tutorial)
identifies Memorial University's StarCraft 1.16.1 distribution as hosted with
Activision Blizzard's permission. The permission statement is a community statement;
we have not independently obtained the underlying permission agreement.

The old university URL returned HTTP 404. Its competition landing page now redirects
to Dave Churchill's site. His [resources page](https://davechurchill.ca/starcraft/resources/)
explicitly links the [minimal 1.16.1 distribution](https://davechurchill.ca/starcraft/files/Starcraft_1161.zip)
for BWAPI. That HTTPS download succeeded. The archive remains in ignored
`downloads/Starcraft_1161.zip`; only the single `StarCraft.exe` entry was extracted
to ignored `original/StarCraft.exe`. No game was executed and no other assets were
extracted. The old Blizzard FTP HTTPS patch endpoint failed certificate validation;
validation was not bypassed.

Observed executable identity:

- SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`
- Size: 1,220,608 bytes.
- PE32, machine i386, preferred image base `0x00400000`.
- VERSIONINFO file/product version `1.16.1.1` (game patch designation 1.16.1).
- Linker 7.10; raw timestamp 1231391178 (2009-01-08 05:06:18 UTC).
- CodeView PDB path contains `Starcraft1.16.1.build` and `BroodWar.pdb`.
- GPTP's `0x004020B0` entry and relevant field offsets corroborated in this file.

This is the project's first pinned specimen, not proof that every regional release
or launcher-modified executable is identical. The PE has no Authenticode security
directory; the hash is an observation, not a publisher signature or certificate.
Do not silently add another hash. Review version resources, executable provenance,
sections and known function regions before explicitly extending `config/target.json`.

All binary-derived exports are local research artifacts. `.gitignore`, output-directory
restrictions and `tools/check-publication` prevent normal publication of originals,
archives, object files, extracted code, strings, decompiler text and analysis reports.
A local pre-commit hook is installed; fresh clones must install it as described in the
README. Never use forced Git additions for these directories or distribute them.

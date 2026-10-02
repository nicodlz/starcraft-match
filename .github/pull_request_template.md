Describe the concrete reconstruction or tooling problem and the resulting change.
See `CONTRIBUTING.md` and `docs/contributing-with-ai.md`.

For function changes, provide:

- Address, original SHA-256 and source/catalog/document paths.
- Entry and extent evidence, ABI, references and provenance; distinguish community names and hypotheses from binary observations.
- Compiler version/profile and flag changes; original and generated sizes; literal exact result or remaining differences.
- Exact verification commands and results. Keep unmeasured metrics unknown and uncorroborated entries exploratory.

For tooling changes, provide reproduction or validation commands and any compatibility limits.

Public review must not include proprietary binaries, assets, extracted binary regions or generated analysis/export dumps. Summarize local evidence instead.

- [ ] Source was written independently; any third-party references and applicable licenses are identified.
- [ ] Relevant build/tests passed, or failures and unavailable checks are explicitly stated.
- [ ] Claimed exact matches cover a corroborated whole function and its observed ABI; uncertain cases are marked exploratory.
- [ ] `make check` passed; the diff contains no proprietary payloads, generated export dumps, credentials or personal data.

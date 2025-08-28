# URL shortner

## Core Functionalities

- Create: shorten(longURL, customAlias?, ttlSeconds?)
- Returns existing short if the same (idempotency), unless TTL/custom differs.
- Use Base62 code from a unique ID (or hash fallback).
- Resolve/Redirect: resolve(code) → long URL (if active & not expired) + increments hit count.
- Delete: delete(code) → disables code.
- Stats: stats(code) → returns metadata (createdAt, hits, target, expired?).
- Custom Alias: validate allowed characters, ensure not taken.
- Expiration: store expiresAt; reject after expiry.

## Short Code Generation

Preferred: monotonically increasing ID (atomic<uint64_t>) → Base62 encoding (0–9, a–z, A–Z).

Collision handling: if custom alias exists or very rare Base62 collision, bump ID and retry.

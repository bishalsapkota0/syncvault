# syncvault
Personal Dropbox Engine built in C++17
# SyncVault

A self-hosted file sync system built from scratch in C++17. Keep a folder in sync across your devices, like a personal Dropbox, running on your own server.

> 🚧 **Work in progress.** Built in stages. See the roadmap below for what's done and what's next.

## What it does (planned)

- **Sync:** a folder stays the same on all your devices automatically. Edit a file on one machine, and it updates on the others.
- **Chunking + dedup:** files are split into chunks and stored by hash, so identical data is stored only once.
- **Delta sync:** only the chunks that changed get uploaded, not the whole file.
- **Sharing:** give other users read-only or read-write access to a folder.
- **Security:** TLS for data in transit, Argon2 password hashing for credentials at rest.

## Architecture (planned)

```
┌──────────────┐         TLS          ┌──────────────────┐
│   Client     │ ◄──────────────────► │     Server       │
│  (Mac)       │   binary protocol    │  (thread pool)   │
│              │                      │                  │
│ FolderWatcher│                      │ ├─ PostgreSQL    │  users, permissions, file metadata
│ Chunker      │                      │ ├─ Redis         │  sessions, rate limiting, cache
│ Hasher       │                      │ └─ Disk          │  chunks stored by hash
└──────────────┘                      └──────────────────┘
```

## Tech stack

| Layer | Tool |
|---|---|
| Core | C++17 |
| Metadata DB | SQLite → PostgreSQL |
| Cache / sessions | Redis (redis-plus-plus) |
| Encryption in transit | OpenSSL (TLS) |
| Password hashing | Argon2 (libsodium) |
| Build | CMake |
| CI | GitHub Actions |
| Deployment | Docker |

## Roadmap

- [ ] **Stage 1:** Chunk a file and hash the chunks
- [ ] **Stage 2:** Local chunk storage with deduplication
- [ ] **Stage 3:** Client folder watcher (FSEvents)
- [ ] **Stage 4:** TCP server and client with a custom binary protocol
- [ ] **Stage 5:** Authentication, TLS, Redis, and SQL
- [ ] **Stage 6:** Server thread pool
- [ ] **Stage 7:** Crash safety (write-ahead log), tests, and benchmarks

## Build and run

```bash
clang++ -std=c++17 src/main.cpp -o main
./main
```

(A CMake build will replace this soon.)

## Benchmarks

Coming in Stage 7: throughput, dedup savings, delta-sync savings, and p50/p99 latency.

## Why I built this

To learn how real sync systems like Dropbox work underneath (chunking, deduplication, concurrency, and secure networking) by building one myself.

# Console Login System (C++)

A simple command-line login/account system written in C++. Supports account
creation, login, and password recovery via a secret key, with user records
persisted to a local text file.

## Features

- **Create Account** — register with a username, email, and password
  (auto-generated or manually chosen), plus a secret key for recovery.
- **Login** — authenticate with a registered email and password.
- **Forgot Password** — recover your password by verifying your email/username
  and secret key.
- **Menu loop** — the program keeps returning to the main menu after each
  action until you choose to exit.
- Basic input validation: email format checking and duplicate-email rejection
  on signup.

## Requirements

- A C++17-compatible compiler (e.g. `g++` 9+)

## Build

```bash
g++ -std=c++17 -Wall -Wextra -o login_system login.cpp
```

## Run

```bash
./login_system
```

You'll see a menu:

```
===================
Login System      ||
===================
|| 1. Login
|| 2. Create Account
|| 3. Forgot Password
|| 4. Exit
===================
```

Pick an option by number. After Login, Create Account, or Forgot Password
completes, the menu is shown again — the program only exits when you choose
option 4.

## Data storage

User records are appended to `users.txt` in the same directory as the
executable, one line per user, comma-separated:

```
username,email,password,secretKey
```

This file is created automatically on first signup.

## Known limitations / security notes

This project is a learning exercise, not a production-ready auth system.
Worth knowing if you build on it:

- **Passwords are stored in plaintext.** For anything beyond a local demo,
  passwords should be hashed with a slow, salted algorithm (e.g. bcrypt,
  scrypt, or Argon2) rather than stored or displayed as-is.
- **The secret key is also stored in plaintext** and is shown back to the
  user in cleartext after signup — same caveat applies.
- **`users.txt` uses a naive comma-separated format.** Commas inside a
  username or secret key are replaced with `;` to avoid corrupting the file,
  but a real project should use a proper serialization format (JSON, SQLite,
  etc.) instead of hand-rolled CSV.
- **No password complexity/length enforcement** on manual passwords.
- **No encryption at rest** for `users.txt` — anyone with filesystem access
  can read all stored credentials.

## Fixes applied in this version

- Main menu now loops until the user selects "Exit" (previously the program
  returned after a single action).
- `forgotPasswd()` previously prompted for the secret key on *every* row
  while scanning `users.txt`, even non-matching ones. It now only prompts
  once the matching account is found.
- Removed a debug `cout` that printed the user's typed secret key to the
  console.
- Signup previously allowed an invalid password-generation choice to fall
  through and save an account with an empty password. It now re-prompts
  until a valid choice (`a`/`m`) is made.
- Added a duplicate-email check on signup (the original had a comment noting
  this was needed but no implementation).
- Sanitized user-supplied username/secret key to prevent commas from
  corrupting the CSV-style storage format.

## License

MIT (or your preferred license — add a `LICENSE` file to the repo).
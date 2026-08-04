# Portfolio P&L Tracker

A lightweight C++20 command-line application for recording trades, tracking open positions, and calculating profit and loss using a simple cost-basis model.

## Overview

Portfolio P&L Tracker stores trades locally in `trades.csv`, reloads them on startup, and maintains per-symbol position data in memory. It is designed for quick portfolio monitoring from the terminal without requiring a database or external service.

## Features

- Record `BUY` and `SELL` trades from the command line
- Persist trade history automatically to `trades.csv`
- Reload saved trades on startup
- Track net quantity and average cost by symbol
- Calculate realized and unrealized P&L
- View full trade history and current open positions

## Requirements

- C++20-compatible compiler
- CMake 3.15 or later
- A POSIX-like shell or terminal

## Build

```bash
cmake -S . -B build
cmake --build build
```

If you prefer the existing debug build directory used in this repository, you can also build there:

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

## Usage

Run the executable with one of the available commands:

```bash
./portfolio <command> [arguments]
```

### Commands

| Command | Description |
| --- | --- |
| `add <BUY\|SELL> <SYMBOL> <QTY> <PRICE>` | Record a new trade and save it to disk |
| `positions <MARKET_PRICE>` | Show current open positions using the supplied market price |
| `history` | Print all saved trades |
| `pnl` | Print realized P&L by symbol |

### Examples

```bash
./portfolio add BUY AAPL 10 180.50
./portfolio add SELL AAPL 4 185.25
./portfolio history
./portfolio positions 190.00
./portfolio pnl
```

## Data Storage

Trades are stored in a pipe-delimited CSV file named `trades.csv` in the project root.

### File format

```text
symbol|side|quantity|price|timestamp|source
```

### Notes

- `timestamp` is generated automatically when a trade is added manually.
- `source` is currently set to `MANUAL` for trades entered through the CLI.
- The file is rewritten each time a trade is added, so it always contains the full trade history.

## Calculation Model

The application uses a simple average-cost approach:

- **BUY** trades increase position size and recalculate average cost.
- **SELL** trades reduce position size and add to realized P&L.
- **Unrealized P&L** is calculated from the current market price you provide to the `positions` command.

## Project Structure

- `main.cpp` - command-line interface and input validation
- `portfolio.h` / `portfolio.cpp` - portfolio state, persistence, and calculations
- `trade.h` - trade data model
- `CMakeLists.txt` - build configuration
- `LICENSE` - project license

## License

This project is licensed under the MIT License. See `LICENSE` for details.

# Portfolio P&L Tracker

Portfolio P&L Tracker is a lightweight C++20 project for recording trades, tracking open positions, and calculating profit and loss over time.

## Features

- Record buy and sell trades
- Persist trade history to a CSV file
- Track net quantity and average cost by symbol
- Calculate realized and unrealized P&L
- Print trade history and open positions

## Tech Stack

- C++20
- CMake
- Standard library containers and file I/O

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Trade Storage

Trades are stored in `trades.csv` using `|` as the delimiter:

```text
symbol|side|quantity|price|timestamp|source
```

## Project Structure

- `main.cpp` - application entry point
- `portfolio.h` / `portfolio.cpp` - portfolio logic
- `trade.h` - trade data model
- `CMakeLists.txt` - build configuration

## License

This project is licensed under the MIT License. See `LICENSE` for details.

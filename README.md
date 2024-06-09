# Normalized Compression Distance 

## Team

| NMec   | Email                 | Name                                                   |
|--------|-----------------------|--------------------------------------------------------|
| 102491 | raquelparadinha@ua.pt | [Raquel Paradinha](https://github.com/raquelparadinha) |
| 103234 | paulojnpinto02@ua.pt  | [Paulo Pinto](https://github.com/Pjnp5)                |
| 103341 | miguelamatos@ua.pt    | [Miguel Matos](https://github.com/mankings)            |
| 103470 | fantao@ua.pt          | [Filipe Antão](https://github.com/fantao)              |

## How to run

```make clean && make all```

```./bin/shazam [ -c compressor] [ -d dataset ] -f sampleFile ```

| Option                                         | Description                    |
|------------------------------------------------|--------------------------------|
| -h                                             | This help                      |
| -v                                             | Verbose mode                   |
| -c [GZIP, BZIP2, LZMA, ZSTD, LZ4, LZO, SNAPPY] | Compressor type (defautl: GZIP)|
| -d (folder)                                    | Dataset folder                 |
| -f (file)                                      | Sample file                    |

## Roadmap

- Implementation
  - implement compression logic using several compressors (gzip, bzip2, lzma, ...)
- Optimization
  - optimize parameters
  - optimize compressor used
  - (optional) optimize GetMaxFreqs
- Report

## Musics Database

| ID | Title                        | Artist                |
|----|------------------------------|-----------------------|
|  1 | Thrown Around                | James Blake           |
|  2 | CHIHIRO                      | Billie Eilish         |
|  3 | HEAVEN TO ME                 | Tyler, The Creator    |
|  4 | Eyes Closed                  | Imagine Dragons       | 
|  5 | Houdini                      | Eminem                |
|  6 | Little Foot Big Foot         | Childish Gambino      |
|  7 | Please Please Please         | Sabrina Carpenter     |
|  8 | FE!N                         | Travis Scott          |
|  9 | 1093                         | Yeat                  |
| 10 | F33l Lik3 Dyin               | Playboi Carti         |
| 11 | Lying 4 fun                  | Yeat                  |
| 12 | on one tonight               | Gunna                 |
| 13 | Too Sweet                    | Hozier                |
| 14 | Music For a Sushi Restaurant | Harry Styles          |
| 15 | Goodie Bag                   | Still Woozy           |
| 16 | Chelas                       | Sara Correia          |
| 17 | Pica Do 7                    | António Zambujo       | 
| 18 | Canção de Engate             | Tiago Bettencourt     | 
| 19 | jingle.tm                    | PTM                   | 
| 20 | Angry                        | The Rolling Stones    | 
| 21 | Dark Necessities             | Red Hot Chili Peppers |
| 22 | Feel Good Inc.               | Gorillaz              | 
| 23 | Party Rock Anthem            | LMFAO                 | 
| 24 | Let's Get It Started         | The Black Eyed Peas   | 
| 25 | Cake By The Ocean            | DNCE                  | 


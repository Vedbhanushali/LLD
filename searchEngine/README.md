# Mini Search Engine

## Data simulation

```
Page 1: "C++ is a powerful programming language"
Page 2: "Python is great for data science"
Page 3: "C++ supports object oriented programming"
Page 4: "Search engines use indexing and ranking"
```

page with id and string content

## Index of pages

will index each page in trie datastructure
user enters keyword -> lookup keyword in trie -> return all page IDs where it appear

```
Word "C++" → [1, 3]

Word "Python" → [2]

Word "programming" → [1, 3]
```

## Ranking

ranking based on frequency/occurence of keyword in that page.

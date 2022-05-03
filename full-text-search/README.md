# Full-text search with inverted index

In text retrieval, full-text search refers to techniques for searching a single computer-stored document or a collection in a full-text database.
The purpose of an [inverted index](https://en.wikipedia.org/wiki/Inverted_index) is to allow fast full-text searches, at a cost of increased processing when a document is added to the database.

# Fulltextové vyhledávání

Program načte ze souboru databázi článků a z druhého souboru či standardního vstupu seznam dotazů. Pro každý dotaz zobrazí na standardním výstupu seznam článků, ve kterých se nacházejí všechna slova z dotazu, včetně úryvku článku obsahující první hledané slovo.   
Každý dotaz se vyhodnocuje synchronizovaným procházením všech seznamů najednou.

# Vstupní formát

- Program očekává 1-2 argumenty: fulltext **soubor_clanky soubor_dotazy**
- Textový soubor **soubor_clanky** obsahuje seznam článků, které se mají na začátku programu načíst. Data každého článku jsou zapsána na 3 po sobě jdoucích řádcích. Jednotlivé 3 řádky každého článku obsahují následující údaje:
  - *Identifikátor článku*: Posloupnost velkých písmen a čísel o celkové délce maximálně 10. Každý článek má unikátní identifikátor a články jsou dle tohoto identifikátoru vzestupně seřazeny.
  - *Název článku*: Text dlouhý maximálně 60 znaků, obsahovat může pouze znaky z dolní ASCII znakové sady (0-127) kromě CR a LF.
  - *Text článku*: Text neomezené délky, obsahovat může pouze znaky z dolní ASCII znakové sady (0-127) kromě CR a LF.

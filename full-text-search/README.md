# Full-text search with inverted index

In text retrieval, full-text search refers to techniques for searching a single computer-stored document or a collection in a full-text database.
The purpose of an [inverted index](https://en.wikipedia.org/wiki/Inverted_index) is to allow fast full-text searches, at a cost of increased processing when a document is added to the database.

# Fulltextové vyhledávání

Program načte ze souboru databázi článků a z druhého souboru či standardního vstupu seznam dotazů. Pro každý dotaz zobrazí na standardním výstupu seznam článků, ve kterých se nacházejí všechna slova z dotazu, včetně úryvku článku obsahující první hledané slovo.   
Každý dotaz se vyhodnocuje synchronizovaným procházením všech seznamů najednou.

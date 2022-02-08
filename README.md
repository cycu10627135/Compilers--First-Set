# **First Set**
## Description
First 是在建構 Parser 時的重要資訊之一，當同時符合多條規則時，能夠用來決定要選擇哪一條規則進行展開。  
First 的定義如下：  
1. 若有一 Nonterminal A，其規則為 A → α1 | α2 | … | αn，則  
    First(A) = 𝐹𝑖𝑟𝑠𝑡(α1) ∪ 𝐹𝑖𝑟𝑠𝑡(α2) ∪ … ∪ 𝐹𝑖𝑟𝑠𝑡(α𝑛)  
2. 若有一 Right Hand Side 為 β1 β2 … βn，則  
    First(𝛽1) = 𝐹𝑖𝑟𝑠𝑡(β1 β2 … β𝑛)  
3. 承上，若 First(𝛽1) = 𝜀，則 First(𝛽2) = 𝐹𝑖𝑟𝑠𝑡(β1 β2 … β𝑛)，以此類推。  
4. 承上，若 First(𝛽𝑛) = 𝜀，則 First(𝛽𝑛) = 𝐹𝑖𝑟𝑠𝑡(β1 β2 … β𝑛) = 𝜀。  
請依據上述規則，計算出讀入 Grammar 的 First Set 並印出。  

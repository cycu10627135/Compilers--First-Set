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
  
## Input Format
每行開頭為一`Nonterminal`，隔一個`空白`後接其規則。  
不同規則會以`|`分隔  
每條規則結束會以`\n`做區隔  
所有規則皆輸入完後，會以`END_OF_GRAMMAR`代表結束。  
`Nonterminal`與`Terminal`皆為單一字母。  
可接受的輸入 Token 如下：  
* 單一大寫字母 A-Z 作為 Nonterminal  
* 單一小寫字母 a-z 作為 Terminal  
* ; 視為字串結尾  
* $ 視為 EOF  
  
※此題不需考慮規則錯誤或輸入錯誤的情況，請以規則正確的前提來作答。  
※此題規則不會有遞迴的情況。  
  
## Output Format
依照 ASCII 編碼由小到大排序`Nonterminal`和`First Set`並印出。  
每行開頭為`Nonterminal`，隔一個空白後印出對應的`First Set`，並換行。  
例如:
    A 的 First Set 為 abc;，則印出 A ;abc。結尾印出 END_OF_FIRST，並換行。  


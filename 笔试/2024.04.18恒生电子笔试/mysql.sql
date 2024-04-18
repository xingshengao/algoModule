--SQL第一题
SELECT c.name, e.contract, e.quantity, e.price
FROM entrust e 
JOIN fund_account f ON e.account = f.account
JOIN client c ON f.client_id = c.client_id
WHERE c.client_id = 10001 AND f.state = 'A' AND e.state = 1
ORDER BY e.quantity * e.price DESC;

--SQL第二题
SELECT 
    SUM(CASE WHEN quantity > 1000 THEN 1 ELSE 0 end) AS quantity_cnt,
    SUM(CASE WHEN price >= 2000 THEN 1 ELSE 0 end) AS price_cnt
FROM 
    entrust AS e
WHERE 
    quantity > 1000 OR price >= 2000;

--SQL第三题
SELECT
    sum(quantity * price)
FROM 
    entrust
WHERE 
    account = 1001 AND LEFT(entrust_time, 8) = '20230718' AND state = '1';


--SQL第四题
SELECT 
    '90 后' AS '年龄段',
    SUM(CASE WHEN SUBSTR(ci.birth, 3, 2) BETWEEN '90' AND '99' THEN ca.credit ELSE 0 END) AS '信用卡余额'
FROM 
    cust_info ci
JOIN 
    cust_assets ca ON ci.no = ca.no
UNION 
SELECT 
    '00 后' AS '年龄段',
    SUM(CASE WHEN SUBSTR(ci.birth, 3, 2) BETWEEN '00' AND '09' THEN ca.credit ELSE 0 END) AS '信用卡余额'
FROM 
    cust_info ci
JOIN 
    cust_assets ca ON ci.no = ca.no;
ATTACH DATABASE 'test.db' AS main;

CREATE TABLE IF NOT EXISTS objects (
    name TEXT NOT NULL,
    x REAL NOT NULL,
    y REAL NOT NULL,
    type TEXT NOT NULL,
    creation_time INTEGER NOT NULL
);
INSERT INTO objects (name, x, y, type, creation_time) VALUES ('Кривой', -37.23, 13.44, 'Человек', 1693235249.98678);
INSERT INTO objects (name, x, y, type, creation_time) VALUES ('Магазин', 0.163, 2.119, 'Здание', 1693135218.173);
INSERT INTO objects (name, x, y, type, creation_time) VALUES ('Лада', 118.3, -982.041, 'Машина', 1692748121.63);
SELECT * FROM objects;

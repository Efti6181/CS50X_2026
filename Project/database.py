import sqlite3
conn = sqlite3.connect("database.db")
conn.execute("""
CREATE TABLE IF NOT EXISTS edges (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    u TEXT,
    v TEXT
)
""")
conn.commit()
conn.close()
print("Database created")
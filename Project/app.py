from flask import Flask, render_template, request
from deadlock import DeadlockDetector
import sqlite3
from collections import defaultdict, deque
app = Flask(__name__)
DB = "database.db"
def get_execution_order(edges):
    graph = defaultdict(list)
    indegree = defaultdict(int)
    nodes = set()
    for u, v in edges:
        graph[u].append(v)
        indegree[v] += 1
        nodes.add(u)
        nodes.add(v)
    queue = deque([n for n in nodes if indegree[n] == 0])
    order = []
    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)
    return order
def create_db():
    conn = sqlite3.connect(DB)
    conn.execute("""
    CREATE TABLE IF NOT EXISTS edges (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        u TEXT,
        v TEXT
    )
    """)
    conn.commit()
    conn.close()
create_db()
@app.route("/", methods=["GET", "POST"])
def index():
    result = None
    safe_order = None
    edges_list = []
    if request.method == "POST":
        detector = DeadlockDetector()
        edges = request.form.get("edges")
        lines = edges.strip().split("\n")
        conn = sqlite3.connect(DB)
        conn.execute("DELETE FROM edges")
        conn.commit()
        for line in lines:
            line = line.strip()
            if "->" in line:
                u, v = line.split("->")
                u = u.strip()
                v = v.strip()
                detector.add_edge(u, v)
                edges_list.append((u, v))
                conn.execute("INSERT INTO edges (u,v) VALUES (?,?)", (u, v))
        conn.commit()
        conn.close()
        if detector.detect_deadlock():
            result = "Deadlock detected"
        else:
            result = "System is safe"
            safe_order = get_execution_order(edges_list)
    return render_template("index.html", result=result, safe_order=safe_order)
@app.route("/saved")
def saved():
    conn = sqlite3.connect(DB)
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT u, v FROM edges")
        rows = cursor.fetchall()
    except sqlite3.Error as e:
        rows = []
        print("Database error:", e)
    finally:
        conn.close()
    return render_template("saved.html", rows=rows)
if __name__ == "__main__":
    app.run(debug=True)
class DeadlockDetector:
    def __init__(self):
        self.graph = {}
    def add_node(self, node):
        if node not in self.graph:
            self.graph[node] = []
    def add_edge(self, u, v):
        self.add_node(u)
        self.add_node(v)
        self.graph[u].append(v)
    def detect_deadlock(self):
        visited = set()
        rec_stack = set()
        for node in self.graph:
            if node not in visited:
                if self.dfs(node, visited, rec_stack):
                    return True
        return False
    def dfs(self, node, visited, rec_stack):
        visited.add(node)
        rec_stack.add(node)
        for neighbor in self.graph[node]:
            if neighbor not in visited:
                if self.dfs(neighbor, visited, rec_stack):
                    return True
            elif neighbor in rec_stack:
                return True
        rec_stack.remove(node)
        return False
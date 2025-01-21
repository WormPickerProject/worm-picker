import os
from graphviz import Digraph

dot = Digraph(format='png', graph_attr={'rankdir': 'TD', 'style': 'filled', 'color': 'lightgrey'})

with dot.subgraph(name='cluster_Initialization') as init:
    init.attr(label='Initialization', style='filled', color='#f0f0f0')
    init.node("Constructor", "TaskManager(node, factory, timer)", style="filled", fillcolor="#e1f5fe", color="#01579b")
    init.node("LoadParams", "Load Parameters", style="filled", fillcolor="#e1f5fe", color="#01579b")
    init.node("InitModeMap", "Initialize mode_map_", style="filled", fillcolor="#e1f5fe", color="#01579b")
    init.node("InitValidator", "Create TaskValidator", style="filled", fillcolor="#e1f5fe", color="#01579b")
    init.edges([("Constructor", "LoadParams"), 
                ("LoadParams", "InitModeMap"), 
                ("LoadParams", "InitValidator")])

with dot.subgraph(name='cluster_Task_Execution') as task_exec:
    task_exec.attr(label='Task Execution', style='filled', color='#e6f3ff')
    task_exec.node("Execute", "executeTask()", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("CheckMode", "Mode Switch?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    task_exec.node("SetEffector", "Set End Effector Parameter", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("CreateTask", "Create Task with Timer", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("PlanTask", "Plan Task with Timer", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("ExecSolution", "Execute Solution with Timer", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("FindSols", "Has Solutions?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    task_exec.node("Error1", "Return Error", style="filled", fillcolor="#ffebee", color="#c62828")
    task_exec.node("ValidateSols", "findValidSolution()", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("CheckValid", "Valid Solution?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    task_exec.node("Error2", "Return Error", style="filled", fillcolor="#ffebee", color="#c62828")
    task_exec.node("ExecutePublishedSol", "Execute Published Solution", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("CheckSuccess", "Success?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    task_exec.node("Error3", "Return Error", style="filled", fillcolor="#ffebee", color="#c62828")
    task_exec.node("Record", "Record Timer Results", style="filled", fillcolor="#e1f5fe", color="#01579b")
    task_exec.node("Success", "Return Success", style="filled", fillcolor="#e8f5e9", color="#2e7d32")
    task_exec.node("CheckSet", "Set Success?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    task_exec.node("Error4", "Return Error", style="filled", fillcolor="#ffebee", color="#c62828")
    
    task_exec.edge("Execute", "CheckMode")
    task_exec.edge("CheckMode", "SetEffector", label="Yes")
    task_exec.edge("CheckMode", "CreateTask", label="No")
    task_exec.edge("CreateTask", "PlanTask")
    task_exec.edge("PlanTask", "ExecSolution")
    task_exec.edge("ExecSolution", "FindSols")
    task_exec.edge("FindSols", "Error1", label="No")
    task_exec.edge("FindSols", "ValidateSols", label="Yes")
    task_exec.edge("ValidateSols", "CheckValid")
    task_exec.edge("CheckValid", "Error2", label="No")
    task_exec.edge("CheckValid", "ExecutePublishedSol", label="Yes")
    task_exec.edge("ExecutePublishedSol", "CheckSuccess")
    task_exec.edge("CheckSuccess", "Error3", label="No")
    task_exec.edge("CheckSuccess", "Record", label="Yes")
    task_exec.edge("Record", "Success")
    task_exec.edge("SetEffector", "CheckSet")
    task_exec.edge("CheckSet", "Error4", label="No")
    task_exec.edge("CheckSet", "Success", label="Yes")

with dot.subgraph(name='cluster_Solution_Validation') as sol_valid:
    sol_valid.attr(label='Solution Validation', style='filled', color='#e8eaf6')
    sol_valid.node("ValidateSols", "findValidSolution()", style="filled", fillcolor="#e1f5fe", color="#01579b")
    sol_valid.node("ForEachSol", "For Each Solution", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    sol_valid.node("CheckFailure", "Is Failure?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    sol_valid.node("NextSol", "Next Solution", style="filled", fillcolor="#e1f5fe", color="#01579b")
    sol_valid.node("Validate", "Validate Solution", style="filled", fillcolor="#e1f5fe", color="#01579b")
    sol_valid.node("CheckState", "Valid State?", shape="diamond", style="filled", fillcolor="#fff3e0", color="#e65100")
    sol_valid.node("ReturnSol", "Return Solution", style="filled", fillcolor="#e8f5e9", color="#2e7d32")
    
    sol_valid.edge("ValidateSols", "ForEachSol")
    sol_valid.edge("ForEachSol", "CheckFailure")
    sol_valid.edge("CheckFailure", "NextSol", label="Yes")
    sol_valid.edge("CheckFailure", "Validate", label="No")
    sol_valid.edge("Validate", "CheckState")
    sol_valid.edge("CheckState", "NextSol", label="No")
    sol_valid.edge("CheckState", "ReturnSol", label="Yes")
    sol_valid.edge("NextSol", "ForEachSol")

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'flowchart_task_execution')
dot.render(file_path, view=False)
file_path
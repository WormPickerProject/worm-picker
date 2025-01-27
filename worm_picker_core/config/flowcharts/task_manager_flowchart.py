import os
import csv
from graphviz import Digraph

def create_task_manager_flowchart():
    dot = Digraph('task_manager', format='png')
    # Change rankdir to LR for left-to-right layout
    dot.attr(rankdir='TB', splines='polyline', compound='true', pad='0.5', nodesep='0.3', ranksep='0.5')

    colors = {
        'primary': '#1E3A8A',
        'secondary': '#3B82F6',
        'success': '#10B981',
        'error': '#EF4444',
        'warning': '#F59E0B',
        'background': '#F9FAFB',
        'text': '#374151',
        'border': '#E5E7EB',
    }

    dot.attr('node', style='rounded,filled',
             fillcolor='#FFFFFF',
             color=colors['secondary'],
             fontsize='10',
             fontname='Helvetica',
             margin='0.15')

    styles = {
        'process': {
            'fillcolor': '#DBEAFE',
            'color': colors['primary'],
            'shape': 'box',
            'fontsize': '12',
        },
        'decision': {
            'fillcolor': '#FEF3C7',
            'color': colors['warning'],
            'shape': 'diamond',
            'fontsize': '12',
        },
        'error': {
            'fillcolor': '#FEE2E2',
            'color': colors['error'],
            'shape': 'box',
            'fontsize': '12',
        },
        'success': {
            'fillcolor': '#D1FAE5',
            'color': colors['success'],
            'shape': 'box',
            'fontsize': '12',
        }
    }

    # Main container
    with dot.subgraph(name='cluster_MainFlow') as main_cluster:
        main_cluster.attr(label='Task Flowchart', bgcolor=colors['background'], 
                         color=colors['border'], fontsize='16')
        
        # Create invisible nodes first to establish ranking
        main_cluster.node('Invisible1', '', style='invis')
        main_cluster.node('Invisible2', '', style='invis')
        
        # Task Execution Cluster
        with main_cluster.subgraph(name='cluster_Execution') as exec_cluster:
            exec_cluster.attr(label='Task Execution', bgcolor=colors['background'], 
                            color=colors['border'])
            exec_cluster.attr(rank='same')
            exec_cluster.attr(labeljust='l')

            process_nodes = [('Execute', 'executeTask()'), 
                           ('SetEffector', 'Set End Effector\nParameter'),
                           ('CreateTask', 'Create Task\nwith Timer'), 
                           ('PlanTask', 'Plan Task\nwith Timer'),
                           ('ExecSolution', 'Execute Solution\nwith Timer'), 
                           ('Record', 'Record Timer\nResults')]
            decision_nodes = [('CheckMode', 'Mode Switch?'), 
                            ('CheckSet', 'Set Success?'), 
                            ('CheckSuccess', 'Success?')]
            error_nodes = [('Error3', 'Task execution failed'), 
                         ('Error4', 'Parameter setting failed')]
            success_nodes = [('Success', 'Success')]

            for group, style in [(process_nodes, 'process'), 
                               (decision_nodes, 'decision'), 
                               (error_nodes, 'error'), 
                               (success_nodes, 'success')]:
                for node_id, label in group:
                    exec_cluster.node(node_id, label, **styles[style])

            edges_exec = [
                ('Execute', 'CheckMode'), 
                ('CheckMode', 'SetEffector', 'Yes'), 
                ('CheckMode', 'CreateTask', 'No'), 
                ('CreateTask', 'PlanTask'), 
                ('PlanTask', 'ExecSolution'), 
                ('SetEffector', 'CheckSet'), 
                ('CheckSet', 'Error4', 'No'), 
                ('CheckSet', 'Success', 'Yes'), 
                ('ExecSolution', 'CheckSuccess'), 
                ('CheckSuccess', 'Error3', 'No'), 
                ('CheckSuccess', 'Record', 'Yes'), 
                ('Record', 'Success')
            ]

            for edge in edges_exec:
                exec_cluster.edge(edge[0], edge[1], label=edge[2] if len(edge) > 2 else None)

        # Solution Execution Cluster
        with main_cluster.subgraph(name='cluster_Solution') as sol_cluster:
            sol_cluster.attr(label='Solution Execution', bgcolor=colors['background'], 
                           color=colors['border'])
            sol_cluster.attr(rank='same')
            sol_cluster.attr(labeljust='l')

            process_nodes_sol = [('ExecuteTask', 'Publish and Execute Task'), 
                               ('ValidateSols', 'Find Valid Solution')]
            decision_nodes_sol = [('CheckValid', 'Valid Solution?'), 
                                ('FindSols', 'Has Solutions?')]
            error_nodes_sol = [('Error1', 'No solutions found'), 
                             ('Error2', 'No valid solutions')]

            for group, style in [(process_nodes_sol, 'process'), 
                               (decision_nodes_sol, 'decision'), 
                               (error_nodes_sol, 'error')]:
                for node_id, label in group:
                    sol_cluster.node(node_id, label, **styles[style])

            edges_sol = [
                ('FindSols', 'ValidateSols', 'Yes'), 
                ('FindSols', 'Error1', 'No'), 
                ('ValidateSols', 'CheckValid'), 
                ('CheckValid', 'Error2', 'No'), 
                ('CheckValid', 'ExecuteTask', 'Yes')
            ]

            for edge in edges_sol:
                sol_cluster.edge(edge[0], edge[1], label=edge[2] if len(edge) > 2 else None)

        # Solution Validation Cluster
        with main_cluster.subgraph(name='cluster_Validation') as valid_cluster:
            valid_cluster.attr(label='Solution Validation', bgcolor=colors['background'], 
                             color=colors['border'])
            valid_cluster.attr(rank='same')
            valid_cluster.attr(labeljust='l')

            process_nodes_valid = [('NextSol', 'Next Solution'), 
                                 ('Validate', 'Validate Solution')]
            decision_nodes_valid = [('ForEachSol', 'For Each Solution'), 
                                  ('CheckFailure', 'Is Failure?'), 
                                  ('CheckState', 'Valid State?')]
            success_nodes_valid = [('ReturnSol', 'Return Valid Solution')]

            for group, style in [(process_nodes_valid, 'process'), 
                               (decision_nodes_valid, 'decision'), 
                               (success_nodes_valid, 'success')]:
                for node_id, label in group:
                    valid_cluster.node(node_id, label, **styles[style])

            edges_valid = [
                ('ForEachSol', 'CheckFailure'), 
                ('CheckFailure', 'NextSol', 'Yes'), 
                ('CheckFailure', 'Validate', 'No'), 
                ('Validate', 'CheckState'), 
                ('CheckState', 'NextSol', 'No'), 
                ('CheckState', 'ReturnSol', 'Yes'), 
                ('NextSol', 'ForEachSol')
            ]

            for edge in edges_valid:
                valid_cluster.edge(edge[0], edge[1], label=edge[2] if len(edge) > 2 else None)

        # Create invisible edges to maintain left-to-right order
        main_cluster.edge('ExecSolution', 'Invisible1', style='invis')
        main_cluster.edge('Invisible1', 'FindSols', style='invis')
        main_cluster.edge('ValidateSols', 'Invisible2', style='invis')
        main_cluster.edge('Invisible2', 'ForEachSol', style='invis')
        
        # Add constraint edges to maintain cluster order
        main_cluster.edge('Invisible1', 'Invisible2', style='invis')

        return dot

def main():
    flowchart = create_task_manager_flowchart()
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # dot_file_path = os.path.join(script_dir, 'task_manager_flowchart.dot')
    # with open(dot_file_path, 'w') as f:
    #     f.write(flowchart.source)
    
    file_path = os.path.join(script_dir, 'task_manager_flowchart')
    flowchart.render(file_path, view=False, cleanup=True)

if __name__ == "__main__":
    main()
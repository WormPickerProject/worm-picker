import os
from graphviz import Digraph

def create_modern_flowchart():
    dot = Digraph('task_manager', format='png')
    # The entire container flows left-to-right:
    dot.attr(rankdir='LR', splines='ortho', compound='true', pad='0.5')

    # Example color palette
    colors = {
        'primary': '#2563EB',
        'secondary': '#3B82F6',
        'success': '#059669',
        'error': '#DC2626',
        'warning': '#D97706',
        'background': '#F8FAFC',
        'text': '#1E293B',
        'light_text': '#64748B',
        'border': '#E2E8F0',
    }

    # Default node style
    dot.attr('node', style='rounded,filled',
                     fillcolor='#FFFFFF',
                     color=colors['secondary'],
                     fontsize='12',
                     height='0.3',
                     width='0.6',
                     margin='0.05',
                     penwidth='1.0')

    # Node style variants
    styles = {
        'process': {
            'style': 'filled,rounded',
            'fillcolor': '#F1F5F9',
            'color': colors['primary'],
            'fontcolor': colors['text'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        },
        'decision': {
            'style': 'filled',
            'fillcolor': '#FEF3C7',
            'color': colors['warning'],
            'fontcolor': colors['text'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'diamond',
            'height': '0.7',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15'
        },
        'error': {
            'style': 'filled,rounded',
            'fillcolor': '#FEE2E2',
            'color': colors['error'],
            'fontcolor': colors['error'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        },
        'success': {
            'style': 'filled,rounded',
            'fillcolor': '#DCFCE7',
            'color': colors['success'],
            'fontcolor': colors['success'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        }
    }

    # Subgraph style
    subgraph_attrs = {
        'style': 'rounded,filled',
        'fillcolor': colors['background'],
        'color': colors['border'],
        'fontname': 'Arial',
        'fontsize': '16',
        'fontcolor': colors['text'],
        'labeljust': 'r',
        'labelloc': 't',
        'margin': '20',
        'penwidth': '1.0'
    }

    # Modern edge styling
    dot.attr('edge', color=colors['secondary'],
                     fontcolor=colors['light_text'],
                     fontsize='10',
                     fontname='Arial',
                     penwidth='1.5',
                     arrowsize='0.8',
                     arrowhead='normal',
                     style='solid')

    # Main cluster (acting as an overall container)
    with dot.subgraph(name='cluster_MainFlow') as main_cluster:
        # The main cluster flows left->right for sub-clusters
        main_cluster.attr(label='Overall Flowchart', rankdir='LR', **subgraph_attrs)

        #--------------------------------------------------
        # 1. Task Execution Cluster
        #--------------------------------------------------
        with main_cluster.subgraph(name='cluster_Exec') as exec_:
            # Inside this sub-cluster, we want top->bottom
            exec_.attr(label='Task Execution', rankdir='TB', **subgraph_attrs)
            
            process_nodes = [
                ('Execute', 'executeTask()'),
                ('SetEffector', 'Set End Effector\nParameter'),
                ('CreateTask', 'Create Task\nwith Timer'),
                ('PlanTask', 'Plan Task\nwith Timer'),
                ('ExecSolution', 'Execute solution\nwith timer'),
                ('Record', 'Record Timer\nResults')
            ]
            
            decision_nodes = [
                ('CheckMode', 'Mode\nSwitch?'),
                ('CheckSet', 'Set\nSuccess?'),
                ('CheckSuccess', 'Success?'),
            ]
            
            error_nodes = [
                ('Error3', 'Task execution\nfailed'),
                ('Error4', 'Parameter setting\nfailed')
            ]
            
            success_nodes = [('Success', 'Success')]

            for group, style_key in [
                (process_nodes, 'process'),
                (decision_nodes, 'decision'),
                (error_nodes, 'error'),
                (success_nodes, 'success')
            ]:
                for node_id, label in group:
                    exec_.node(node_id, label, **styles[style_key])

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
                if len(edge) == 3:
                    exec_.edge(edge[0], edge[1], label=edge[2])
                else:
                    exec_.edge(edge[0], edge[1])

        #--------------------------------------------------
        # 2. Solution Execution Cluster
        #--------------------------------------------------
        with main_cluster.subgraph(name='cluster_ExecSol') as exec_sol:
            exec_sol.attr(label='Solution Execution', rankdir='TB', **subgraph_attrs)
            
            process_nodes_sol = [
                ('ExecuteTask', 'Publish and\nExecute Task'),
                ('ValidateSols', 'Find Valid\nSolution'),
            ]

            decision_nodes_sol = [
                ('CheckValid', 'Valid\nSolution?'),
                ('FindSols', 'Has\nSolutions?')
            ]
            
            error_nodes_sol = [
                ('Error1', 'No solutions\nfound'),
                ('Error2', 'No valid\nsolutions')
            ]
            
            for group, style_key in [
                (process_nodes_sol, 'process'),
                (decision_nodes_sol, 'decision'),
                (error_nodes_sol, 'error')
            ]:
                for node_id, label in group:
                    exec_sol.node(node_id, label, **styles[style_key])

            edges_sol = [
                ('FindSols', 'Error1', 'No'),
                ('FindSols', 'ValidateSols', 'Yes'),
                ('ValidateSols', 'CheckValid'),
                ('CheckValid', 'Error2', 'No'),
                ('CheckValid', 'ExecuteTask', 'Yes')
            ]
            
            for edge in edges_sol:
                if len(edge) == 3:
                    exec_sol.attr(ordering='out')
                    exec_sol.edge(edge[0], edge[1], style='invis')
                    exec_sol.edge(edge[0], edge[1], label=edge[2])
                else:
                    exec_sol.attr(ordering='out')
                    exec_sol.edge(edge[0], edge[1], style='invis')
                    exec_sol.edge(edge[0], edge[1])

        #--------------------------------------------------
        # 3. Solution Validation Cluster
        #--------------------------------------------------
        with main_cluster.subgraph(name='cluster_Valid') as valid:
            valid.attr(label='Solution Validation', rankdir='TB', **subgraph_attrs)
            
            process_nodes_valid = [
                ('NextSol', 'Next\nSolution'),
                ('Validate', 'Validate\nSolution')
            ]

            process_nodes_valid = [
                ('NextSol', 'Next\nSolution'),
                ('Validate', 'Validate\nSolution')
            ]
            
            decision_nodes_valid = [
                ('ForEachSol', 'For Each\nSolution'),
                ('CheckFailure', 'Is\nFailure?'),
                ('CheckState', 'Valid\nState?')
            ]
            
            success_nodes_valid = [
                ('ReturnSol', 'Return Valid\nSolution')
            ]

            for group, style_key in [
                (process_nodes_valid, 'process'),
                (decision_nodes_valid, 'decision'),
                (success_nodes_valid, 'success')
            ]:
                for node_id, label in group:
                    valid.node(node_id, label, **styles[style_key])

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
                if len(edge) == 3:
                    valid.attr(ordering='out')
                    valid.edge(edge[0], edge[1], style='invis')
                    valid.edge(edge[0], edge[1], label=edge[2])
                else:
                    valid.attr(ordering='out')
                    valid.edge(edge[0], edge[1], style='invis')
                    valid.edge(edge[0], edge[1])

        # If you still have edges connecting nodes in different subclusters:
        main_cluster.edge('ExecSolution', 'FindSols', constraint='true', minlen='2')
        main_cluster.edge('ValidateSols', 'ForEachSol', constraint='true', minlen='2')

    return dot

def main():
    flowchart = create_modern_flowchart()
    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(script_dir, 'modern_task_flowchart')
    flowchart.render(file_path, view=False, cleanup=True)

if __name__ == "__main__":
    main()
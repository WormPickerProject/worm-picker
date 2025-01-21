import os
from graphviz import Digraph

def create_task_manager_flowchart():
    dot = Digraph('task_manager', format='png')

    # ============ Potential Toggles (Comment/Uncomment) ============

    # 1. Layout Engine (default is 'dot'):
    dot.engine = 'dot'    # Hierarchical (default)
    # dot.engine = 'neato'  # Force-directed
    # dot.engine = 'fdp'    # Another force-directed approach
    # dot.engine = 'sfdp'   # Multiscale force-directed
    # dot.engine = 'twopi'  # Radial layout

    # 2. Direction:
    # dot.attr(rankdir='TB')  # Top to bottom
    dot.attr(rankdir='LR')  # Left to right (default from your snippet)
    # dot.attr(rankdir='BT')  # Bottom to top
    # dot.attr(rankdir='RL')  # Right to left

    # 3. Edge Routing (splines):
    dot.attr(splines='true')     # Default curved splines
    # dot.attr(splines='ortho')    # Orthogonal connectors
    # dot.attr(splines='polyline') # Angled straight segments
    # dot.attr(splines='line')     # Straight line edges

    # 4. Overlap:
    dot.attr(overlap='false') # Force Graphviz to attempt removing overlaps (mostly for 'neato'/'fdp')
    dot.attr(overlap='scale') # Scales the layout to reduce overlaps

    # 5. Subgraph Ranking:
    # dot.attr(newrank='true') # Allows subgraphs to have independent rankings (for advanced layering)
    
    # 6. Background color:
    # dot.attr(bgcolor='#FFFFFF') # White background (default)

    # ============ Core Attributes (Recommended Defaults) ============
    dot.attr(
        # rankdir='LR',            # Left to right
        compound='true',
        fontname='Helvetica',    # Clean, professional font
        fontsize='12',           # Slightly larger font size
        nodesep='0.75',
        ranksep='0.75',
        # splines='ortho',         # Orthogonal edge routing
        bgcolor='#FFFFFF'        # White background
    )

    # Updated color palette and styling
    styles = {
        'process': {
            'style': 'filled',
            'fillcolor': '#E8EAF6',  # Light lavender/blue
            'color': '#3949AB',      # Medium blue border
            'fontcolor': '#333333',  # Dark gray text
            'penwidth': '2.0',
            'fontname': 'Helvetica',
            'shape': 'rectangle',
            'height': '0.6',
            'margin': '0.3'
        },
        'decision': {
            'style': 'filled',
            'fillcolor': '#FFF3E0',  # Light orange
            'color': '#FB8C00',      # Bright orange border
            'fontcolor': '#333333',
            'penwidth': '2.0',
            'fontname': 'Helvetica',
            'shape': 'diamond',
            'height': '0.8',
            'margin': '0.3'
        },
        'error': {
            'style': 'filled',
            'fillcolor': '#FFEBEE',  # Light red/pink
            'color': '#D32F2F',      # Red border
            'fontcolor': '#333333',
            'penwidth': '2.0',
            'fontname': 'Helvetica',
            'shape': 'rectangle',
            'height': '0.6',
            'margin': '0.3'
        },
        'success': {
            'style': 'filled',
            'fillcolor': '#E8F5E9',  # Light green
            'color': '#388E3C',      # Darker green border
            'fontcolor': '#333333',
            'penwidth': '2.0',
            'fontname': 'Helvetica',
            'shape': 'rectangle',
            'height': '0.6',
            'margin': '0.3'
        }
    }

    # Subgraph attributes for clustering
    subgraph_attrs = {
        'style': 'filled',
        'fillcolor': '#F5F5F5',  # Neutral light gray
        'color': '#90A4AE',      # Subdued border color
        'fontname': 'Helvetica',
        'fontsize': '14',
        'labeljust': 'l',        # Left align subgraph labels
        'labelloc': 't',         # Place label at the top
        'margin': '12'           # Reduce margin for less bulky subgraphs
    }

    # Default edge styling
    dot.attr('edge', {
        'color': '#1565C0',      # A darker blue for edges
        'penwidth': '2.0',
        'fontname': 'Helvetica',
        'fontsize': '11',
        'fontcolor': '#333333'
    })

    # =========== Initialization Subgraph =============
    with dot.subgraph(name='cluster_Init') as init:
        init.attr(label='Initialization', **subgraph_attrs)

        nodes = [
            ('Constructor', 'TaskManager\n(node, factory,\ntimer)'),
            ('LoadParams', 'Load\nParameters'),
            ('InitModeMap', 'Initialize\nmode_map_'),
            ('InitValidator', 'Create\nTaskValidator')
        ]
        
        for node_id, label in nodes:
            init.node(node_id, label, **styles['process'])
            
        # Edges within Initialization
        init.edges([
            ('Constructor', 'LoadParams'),
            ('LoadParams', 'InitModeMap'),
            ('LoadParams', 'InitValidator')
        ])

    # =========== Task Execution Subgraph =============
    with dot.subgraph(name='cluster_Exec') as exec_:
        exec_.attr(label='Task Execution', **subgraph_attrs)

        # Group nodes by style for convenience
        process_nodes = [
            ('Execute', 'executeTask()'),
            ('SetEffector', 'Set End Effector\nParameter'),
            ('CreateTask', 'Create Task\nwith Timer'),
            ('PlanTask', 'Plan Task\nwith Timer'),
            ('ExecSolution', 'Execute Solution\nwith Timer'),
            ('ValidateSols', 'findValidSolution()'),
            ('ExecuteTask', 'Publish\nand Execute Task'),
            ('Record', 'Record Timer\nResults')
        ]
        
        decision_nodes = [
            ('CheckMode', 'Mode\nSwitch?'),
            ('FindSols', 'Has\nSolutions?'),
            ('CheckValid', 'Valid\nSolution?'),
            ('CheckSuccess', 'Success?'),
            ('CheckSet', 'Set\nSuccess?')
        ]
        
        error_nodes = [
            ('Error1', 'Result::error\nNo solutions found'),
            ('Error2', 'Result::error\nNo valid solutions'),
            ('Error3', 'Result::error\nTask execution failed'),
            ('Error4', 'Result::error\nFailed to set parameter')
        ]
        
        success_nodes = [('Success', 'Result::success')]

        # Create the nodes in the subgraph
        for nodes_group, style in [
            (process_nodes, 'process'),
            (decision_nodes, 'decision'),
            (error_nodes, 'error'),
            (success_nodes, 'success')
        ]:
            for node_id, label in nodes_group:
                exec_.node(node_id, label, **styles[style])

        # Edges within Task Execution
        edges = [
            ('Execute', 'CheckMode'),
            ('CheckMode', 'SetEffector', 'Yes'),
            ('CheckMode', 'CreateTask', 'No'),
            ('CreateTask', 'PlanTask'),
            ('PlanTask', 'ExecSolution'),
            ('ExecSolution', 'FindSols'),
            ('FindSols', 'Error1', 'No'),
            ('FindSols', 'ValidateSols', 'Yes'),
            ('ValidateSols', 'CheckValid'),
            ('CheckValid', 'Error2', 'No'),
            ('CheckValid', 'ExecuteTask', 'Yes'),
            ('ExecuteTask', 'CheckSuccess'),
            ('CheckSuccess', 'Error3', 'No'),
            ('CheckSuccess', 'Record', 'Yes'),
            ('Record', 'Success'),
            ('SetEffector', 'CheckSet'),
            ('CheckSet', 'Error4', 'No'),
            ('CheckSet', 'Success', 'Yes')
        ]

        # Add edges with optional labels
        for edge in edges:
            if len(edge) == 2:
                # No label provided
                exec_.edge(edge[0], edge[1])
            else:
                # There's a label (e.g., "Yes" or "No")
                label_str = edge[2]
                if label_str in ("Yes", "No"):
                    exec_.edge(
                        edge[0], 
                        edge[1],
                        label=label_str,
                        fontsize='16',         # Larger font for the label
                        labelfloat='false',    # Let Graphviz position the label away from the edge
                        labeldistance='5',   # Offset distance from the arrow/edge
                        labelangle='0'         # Angle of the label relative to the edge
                    )
                else:
                    # For other labels
                    exec_.edge(edge[0], edge[1], label=label_str)

    # =========== Solution Validation Subgraph =============
    with dot.subgraph(name='cluster_Valid') as valid:
        valid.attr(label='Solution Validation', **subgraph_attrs)

        process_nodes = [
            ('NextSol', 'Next\nSolution'),
            ('Validate', 'Validate Solution\nvia task_validator_')
        ]
        
        decision_nodes = [
            ('ForEachSol', 'For Each\nSolution'),
            ('CheckFailure', 'Is\nFailure?'),
            ('CheckState', 'Valid\nState?')
        ]

        success_nodes = [('ReturnSol', 'Return\nValid Solution')]

        for nodes_group, style in [
            (process_nodes, 'process'),
            (decision_nodes, 'decision'),
            (success_nodes, 'success')
        ]:
            for node_id, label in nodes_group:
                valid.node(node_id, label, **styles[style])

        edges = [
            ('ValidateSols', 'ForEachSol'),
            ('ForEachSol', 'CheckFailure'),
            ('CheckFailure', 'NextSol', 'Yes'),
            ('CheckFailure', 'Validate', 'No'),
            ('Validate', 'CheckState'),
            ('CheckState', 'NextSol', 'No'),
            ('CheckState', 'ReturnSol', 'Yes'),
            ('NextSol', 'ForEachSol')
        ]

        # for edge in edges:
        #     if len(edge) == 2:
        #         valid.edge(edge[0], edge[1])
        #     else:
        #         valid.edge(edge[0], edge[1], xlabel=edge[2])
        for edge in edges:
            if len(edge) == 2:
                # No label provided
                valid.edge(edge[0], edge[1])
            else:
                # There's a label (e.g., "Yes" or "No")
                label_str = edge[2]
                if label_str in ("Yes", "No"):
                    valid.edge(
                        edge[0], 
                        edge[1],
                        xlabel=label_str,
                        fontsize='16',         # Larger font for the label
                        labelfloat='false',    # Let Graphviz position the label away from the edge
                        labeldistance='5',   # Offset distance from the arrow/edge
                        labelangle='0'         # Angle of the label relative to the edge
                    )
                else:
                    # For other labels
                    valid.edge(edge[0], edge[1], label=label_str)

    return dot

def main():
    flowchart = create_task_manager_flowchart()
    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(script_dir, 'flowchart_task_execution_2')
    flowchart.render(file_path, view=False, cleanup=True)

if __name__ == "__main__":
    main()
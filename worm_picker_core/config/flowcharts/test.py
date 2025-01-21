import os
from graphviz import Digraph

def create_modern_flowchart():
    # Core layout engine selection
    dot = Digraph('task_manager', format='png')
    dot.engine = 'dot'  # Hierarchical layout optimized for flow direction and minimal edge crossings
    
    # Global graph attributes
    dot.attr(
        rankdir='TB',      # Top-to-Bottom flow direction for natural reading
        # splines='ortho',   # Creates right-angled edge connections for cleaner visual structure
        ranksep='0.5',    # Vertical space between ranks (rows) of nodes for clear hierarchy
        nodesep='0.5',     # Horizontal space between nodes at same rank for reduced cluttering
        compound='true',   # Enables edges between clusters and better subgraph handling
        pad='0.5',         # External padding around entire graph for visual breathing room
    )

    # Modern color palette using Tailwind-inspired colors
    colors = {
        'primary': '#2563EB',     # Strong blue for primary actions/main flow
        'secondary': '#3B82F6',   # Softer blue for supporting elements
        'success': '#059669',     # Muted green for positive outcomes
        'error': '#DC2626',       # Bright red for error states
        'warning': '#D97706',     # Deep amber for decision points
        'background': '#F8FAFC',  # Cool gray for subtle container backgrounds
        'text': '#1E293B',        # Deep slate for primary text
        'light_text': '#64748B',  # Medium slate for secondary text
        'border': '#E2E8F0',      # Light cool gray for subtle boundaries
    }

    dot.attr('node', {
        'style': 'rounded,filled',
        'fillcolor': '#FFFFFF',
        'color': colors['secondary'],
        'fontsize': '12',
        'height': '0.3',
        'width': '0.6',
        'margin': '0.05',
        'penwidth': '1.0'
    })

    # Modern node styles with consistent typography and spacing
    styles = {
        'process': {
            'style': 'filled,rounded',  # Combines fill with rounded corners for modern appearance
            'fillcolor': '#F1F5F9',     # Light blue-gray fill for neutral process steps
            'color': colors['primary'], # Blue outline creates visual hierarchy
            'fontcolor': colors['text'], # Dark slate text for optimal readability
            'fontname': 'Arial',        # Clean, modern sans-serif font
            'fontsize': '14',           # Large text size for better visibility
            'shape': 'box',             # Rectangular shape indicates process step
            'height': '0.5',            # Compact height for dense layouts
            'width': '1.6',             # Width accommodates typical label length
            'penwidth': '1.5',          # Medium border weight for definition
            'margin': '0.15,0.1'        # Minimal internal padding for compact look
        },
        'decision': {
            'style': 'filled',          # Solid fill distinguishes decision points
            'fillcolor': '#FEF3C7',     # Warm amber background signals choice points
            'color': colors['warning'], # Orange border reinforces decision state
            'fontcolor': colors['text'], # Consistent text color for readability
            'fontname': 'Arial',        # Maintains font consistency across nodes
            'fontsize': '14',           # Matches process node text size
            'shape': 'diamond',         # Traditional diamond shape signals decision
            'height': '0.7',            # Slightly taller to accommodate diamond shape
            'width': '1.6',             # Balanced width for diamond proportions
            'penwidth': '1.5',          # Consistent border weight with other nodes
            'margin': '0.15'            # Uniform padding for diamond shape
        },
        'error': {
            'style': 'filled,rounded',  # Rounded corners soften error state appearance
            'fillcolor': '#FEE2E2',     # Light red background signals error condition
            'color': colors['error'],   # Red border emphasizes error state
            'fontcolor': colors['error'], # Red text reinforces error messaging
            'fontname': 'Arial',        # Consistent font family across all nodes
            'fontsize': '14',           # Matching text size for visual harmony
            'shape': 'box',             # Rectangular shape like process nodes
            'height': '0.5',            # Maintains consistent node heights
            'width': '1.6',             # Standard width for layout consistency
            'penwidth': '1.5',          # Consistent border weight across nodes
            'margin': '0.15,0.1'        # Compact internal padding matches process nodes
        },
        'success': {
            'style': 'filled,rounded',  # Rounded corners for success state
            'fillcolor': '#DCFCE7',     # Light green signals successful completion
            'color': colors['success'], # Green border reinforces success
            'fontcolor': colors['success'], # Green text emphasizes positive outcome
            'fontname': 'Arial',        # Maintains font consistency
            'fontsize': '14',           # Consistent text size
            'shape': 'box',             # Standard shape for endpoints
            'height': '0.5',            # Consistent height
            'width': '1.6',             # Standard width
            'penwidth': '1.5',          # Consistent border weight
            'margin': '0.15,0.1'        # Consistent padding
        }
    }

    # Subgraph/cluster styling for logical grouping
    subgraph_attrs = {
        'style': 'rounded,filled',    # Rounded corners soften cluster boundaries
        'fillcolor': colors['background'], # Light background creates subtle grouping
        'color': colors['border'],    # Subtle border defines cluster boundaries
        'fontname': 'Arial',          # Consistent font family for headers
        'fontsize': '16',             # Larger text for cluster labels
        'fontcolor': colors['text'],  # Dark text for cluster headers
        'labeljust': 'r',             # Right-aligned labels for modern look
        'labelloc': 't',              # Top-positioned labels for clear hierarchy
        'margin': '20',               # Large margin creates visual separation
        'penwidth': '1.0'             # Thin border for subtle containment
    }

    dot.attr('edge', {
        'color': colors['secondary'],
        # 'penwidth': '1.2',
        # 'arrowsize': '0.8',
        # 'arrowhead': 'vee',
        # 'minlen': '1.5',
        # 'labelboxstyle': 'rounded,filled',
        # 'labelbgcolor': '#FFFFFF',
        # 'labelboxcolor': colors['secondary'],
        # 'labelboxpenwidth': '1.0',
        # 'labelboxmargin': '0.1'
    })

    # Task Execution Cluster
    with dot.subgraph(name='cluster_Exec') as exec_:
        exec_.attr(label='Task Execution', **subgraph_attrs)
        
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

        # Define edges with modern styling
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
            if len(edge) == 2:
                exec_.edge(edge[0], edge[1])
            else:
                exec_.edge(
                    edge[0],
                    edge[1],
                    label=edge[2],  # Add underline using markdown
                    fontsize='11',              # Slightly smaller font
                    labelfloat='true',          # Allows better positioning
                    labeldistance='1.2',        # Closer to the line
                    labelangle='25',            # Angle follows line direction
                    labeljust='l',              # Left justify for angled text
                    fontname='Arial',           
                    fontcolor=colors['text'],
                    penwidth='1.2',
                    constraint='true'
                )

    # Solution Execution Cluster
    with dot.subgraph(name='cluster_ExecSol') as exec_sol:
        exec_sol.attr(label='Solution Execution', **subgraph_attrs)
        
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
            if len(edge) == 2:
                exec_sol.edge(edge[0], edge[1])
            else:
                exec_sol.edge(
                    edge[0],
                    edge[1],
                    label=edge[2],  # Add underline using markdown
                    fontsize='11',              # Slightly smaller font
                    labelfloat='true',          # Allows better positioning
                    labeldistance='1.2',        # Closer to the line
                    labelangle='25',            # Angle follows line direction
                    labeljust='l',              # Left justify for angled text
                    fontname='Arial',           
                    fontcolor=colors['text'],
                    penwidth='1.2',
                    constraint='true'
                )

    # Solution Validation Cluster
    with dot.subgraph(name='cluster_Valid') as valid:
        valid.attr(label='Solution Validation', **subgraph_attrs)
        
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
            if len(edge) == 2:
                valid.edge(edge[0], edge[1])
            else:
                valid.edge(
                    edge[0],
                    edge[1],
                    label=edge[2],  # Add underline using markdown
                    # fontsize='11',              # Slightly smaller font
                    # labelfloat='true',          # Allows better positioning
                    # labeldistance='1.2',        # Closer to the line
                    # labelangle='25',            # Angle follows line direction
                    # labeljust='l',              # Left justify for angled text
                    # fontname='Arial',           
                    # fontcolor=colors['text'],
                    # penwidth='1.2',
                    # constraint='true'
                )

    # Connecting edges between clusters
    dot.edge('ExecSolution', 'FindSols', constraint='true', minlen='2')
    dot.edge('ValidateSols', 'ForEachSol', constraint='true', minlen='2')
    
    return dot

def main():
    flowchart = create_modern_flowchart()
    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(script_dir, 'modern_task_flowchart')
    flowchart.render(file_path, view=False, cleanup=True)

if __name__ == "__main__":
    main()
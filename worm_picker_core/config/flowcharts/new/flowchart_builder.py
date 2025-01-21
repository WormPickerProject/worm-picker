"""
flowchart_builder.py

This module contains the logic for constructing a 'modern' flowchart
using Graphviz. It leverages helper functions and style definitions
from style_config.py to reduce repetition and improve maintainability.
"""

from typing import List, Tuple
from graphviz import Digraph
import style_config

def _create_task_execution_subgraph(
    parent: Digraph,
    node_styles: dict,
    subgraph_attrs: dict
) -> None:
    """
    Creates the 'Task Execution' subgraph within the parent Digraph.
    
    Args:
        parent: The parent Digraph to attach the subgraph to.
        node_styles: Dictionary of node styles keyed by node type.
        subgraph_attrs: Attributes used for the subgraph styling.
    """
    with parent.subgraph(name='cluster_Exec') as exec_:
        exec_.attr(label='Task Execution', **subgraph_attrs)

        # Define nodes
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

        # Add nodes to subgraph
        for node_id, label in process_nodes:
            exec_.node(node_id, label, **node_styles['process'])
        for node_id, label in decision_nodes:
            exec_.node(node_id, label, **node_styles['decision'])
        for node_id, label in error_nodes:
            exec_.node(node_id, label, **node_styles['error'])
        for node_id, label in success_nodes:
            exec_.node(node_id, label, **node_styles['success'])

        # Define edges for task execution
        edges_exec: List[Tuple[str, str, str]] = [
            ('Execute', 'CheckMode', ''),         # no label
            ('CheckMode', 'SetEffector', 'Yes'),
            ('CheckMode', 'CreateTask', 'No'),
            ('CreateTask', 'PlanTask', ''),
            ('PlanTask', 'ExecSolution', ''),
            ('SetEffector', 'CheckSet', ''),
            ('CheckSet', 'Error4', 'No'),
            ('CheckSet', 'Success', 'Yes'),
            ('ExecSolution', 'CheckSuccess', ''),
            ('CheckSuccess', 'Error3', 'No'),
            ('CheckSuccess', 'Record', 'Yes'),
            ('Record', 'Success', '')
        ]

        _add_angled_edges(exec_, edges_exec)


def _create_solution_execution_subgraph(
    parent: Digraph,
    node_styles: dict,
    subgraph_attrs: dict
) -> None:
    """
    Creates the 'Solution Execution' subgraph within the parent Digraph.

    Args:
        parent: The parent Digraph to attach the subgraph to.
        node_styles: Dictionary of node styles keyed by node type.
        subgraph_attrs: Attributes used for the subgraph styling.
    """
    with parent.subgraph(name='cluster_ExecSol') as exec_sol:
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

        # Add nodes
        for node_id, label in process_nodes_sol:
            exec_sol.node(node_id, label, **node_styles['process'])
        for node_id, label in decision_nodes_sol:
            exec_sol.node(node_id, label, **node_styles['decision'])
        for node_id, label in error_nodes_sol:
            exec_sol.node(node_id, label, **node_styles['error'])

        # Define edges for solution execution
        # (start_node, end_node, label)
        edges_sol: List[Tuple[str, str, str]] = [
            ('FindSols', 'Error1', 'No'),
            ('FindSols', 'ValidateSols', 'Yes'),
            ('ValidateSols', 'CheckValid', ''),
            ('CheckValid', 'Error2', 'No'),
            ('CheckValid', 'ExecuteTask', 'Yes')
        ]

        _add_bold_edges(exec_sol, edges_sol)


def _create_solution_validation_subgraph(
    parent: Digraph,
    node_styles: dict,
    subgraph_attrs: dict
) -> None:
    """
    Creates the 'Solution Validation' subgraph within the parent Digraph.

    Args:
        parent: The parent Digraph to attach the subgraph to.
        node_styles: Dictionary of node styles keyed by node type.
        subgraph_attrs: Attributes used for the subgraph styling.
    """
    with parent.subgraph(name='cluster_Valid') as valid:
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

        # Add nodes
        for node_id, label in process_nodes_valid:
            valid.node(node_id, label, **node_styles['process'])
        for node_id, label in decision_nodes_valid:
            valid.node(node_id, label, **node_styles['decision'])
        for node_id, label in success_nodes_valid:
            valid.node(node_id, label, **node_styles['success'])

        # Define edges for solution validation
        edges_valid: List[Tuple[str, str, str]] = [
            ('ForEachSol', 'CheckFailure', ''),
            ('CheckFailure', 'NextSol', 'Yes'),
            ('CheckFailure', 'Validate', 'No'),
            ('Validate', 'CheckState', ''),
            ('CheckState', 'NextSol', 'No'),
            ('CheckState', 'ReturnSol', 'Yes'),
            ('NextSol', 'ForEachSol', '')
        ]

        _add_bold_edges(valid, edges_valid)


def _add_angled_edges(subgraph: Digraph, edges: List[Tuple[str, str, str]]) -> None:
    """
    Adds edges to the given subgraph, with angled labels for 'Yes/No' branches.

    Args:
        subgraph: The subgraph to which the edges will be added.
        edges: A list of tuples (start_node, end_node, label).
    """
    for edge in edges:
        start_node, end_node, label = edge
        if label:
            # Add underline with markdown for the label
            subgraph.edge(
                start_node,
                end_node,
                label='_' + label + '_',
                fontsize='11',
                labelfloat='true',
                labeldistance='1.2',
                labelangle='25',
                labeljust='l',
                fontname='Arial',
                fontcolor='#1E293B',
                penwidth='1.2',
                constraint='true'
            )
        else:
            subgraph.edge(start_node, end_node)


def _add_bold_edges(subgraph: Digraph, edges: List[Tuple[str, str, str]]) -> None:
    """
    Adds edges to the given subgraph with bold styling and a
    horizontally-aligned label.

    Args:
        subgraph: The subgraph to which the edges will be added.
        edges: A list of tuples (start_node, end_node, label).
    """
    for edge in edges:
        start_node, end_node, label = edge
        if label:
            subgraph.edge(
                start_node,
                end_node,
                label=label,
                labeltooltip=label,
                fontsize='12',
                labelfloat='false',
                labeldistance='2',
                labelangle='0',
                labeljust='c',
                penwidth='1.2',
                style='bold',
                decorate='true',
                labelfontname='Arial',
                labelfontcolor='#1E293B',
                labelfontsize='12',
                labelboxstyle='rounded,filled',
                labelbgcolor='#FFFFFF',
                labelboxcolor='#3B82F6',
                labelboxpenwidth='1.0',
                labelboxmargin='0.1'
            )
        else:
            subgraph.edge(start_node, end_node)


def create_modern_flowchart() -> Digraph:
    """
    Creates the entire modern flowchart and returns a Digraph object.

    Returns:
        A fully constructed Graphviz Digraph representing the flowchart.
    """
    # Retrieve styling configurations
    colors = style_config.get_colors()
    node_styles = style_config.get_node_styles(colors)
    subgraph_attrs = style_config.get_subgraph_attrs(colors)
    edge_attrs = style_config.get_edge_attrs(colors)

    dot = Digraph('task_manager', format='png')
    dot.engine = 'dot'

    # Global graph attributes
    dot.attr(
        rankdir='TB',
        splines='ortho',
        ranksep='0.5',
        nodesep='0.5',
        compound='true',
        pad='0.5'
    )

    # Apply default edge style
    dot.attr('edge', **edge_attrs)

    # Apply default node style (as a baseline)
    dot.attr(
        'node',
        style='rounded,filled',
        fillcolor='#FFFFFF',
        color=colors['secondary'],
        fontsize='12',
        height='0.3',
        width='0.6',
        margin='0.05',
        penwidth='1.0'
    )

    # Create subgraphs
    _create_task_execution_subgraph(dot, node_styles, subgraph_attrs)
    _create_solution_execution_subgraph(dot, node_styles, subgraph_attrs)
    _create_solution_validation_subgraph(dot, node_styles, subgraph_attrs)

    # Connect subgraphs
    dot.edge('ExecSolution', 'FindSols', constraint='true', minlen='2')
    dot.edge('ValidateSols', 'ForEachSol', constraint='true', minlen='2')

    return dot
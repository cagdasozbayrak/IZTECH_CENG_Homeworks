import numpy as np


def probability_of_state(current_probability, transition_probability, emission_probability):
    return current_probability * transition_probability * emission_probability


def decide_state(states, current_state_probability, emission_probability, observation, previous_state='', transition_probability={}):
    max_probability = -1
    selected_state = ''

    for state in states:
        state_probability = -1

        # State probability to select a starting state
        if previous_state == '':
            state_probability = probability_of_state(current_state_probability[state], 1, emission_probability[state][observation[0]])

        # State probability for other states
        else:
            transitionProbability = transition_probability[previous_state][state]
            state_probability = probability_of_state(current_state_probability, transitionProbability, emission_probability[state][observation])

        # Select the most probable state
        if state_probability > max_probability:
            max_probability = state_probability
            selected_state = state

    return selected_state, max_probability


def viterbi_algorithm(states, start_probabilities, emission_probability, observations):

    most_likely_sequence = np.array([])

    # Decide the first state
    selected_state, current_state_probability = decide_state(states, start_probabilities, emission_probability, observations)
    most_likely_sequence = np.append(most_likely_sequence, selected_state)

    # Make decisions according to obvervations for next days
    for day in range(len(observations)-1):
        selected_state, current_state_probability = decide_state(states, current_state_probability, emission_probability, observations[day + 1], most_likely_sequence[day], transition_probability)
        most_likely_sequence = np.append(most_likely_sequence, selected_state)

    return most_likely_sequence


if __name__ == '__main__':

    states = {'Rainy', 'Sunny'}
    start_probability = {'Rainy': 0.6, 'Sunny': 0.4}

    transition_probability = {
        'Rainy': {'Rainy': 0.7, 'Sunny': 0.4},
        'Sunny': {'Rainy': 0.4, 'Sunny': 0.6},
    }
    emission_probability = {
        'Rainy': {'walk': 0.1, 'shop': 0.4, 'clean': 0.5},
        'Sunny': {'walk': 0.6, 'shop': 0.3, 'clean': 0.1},
    }

    observations = ('walk', 'walk', 'shop', 'walk', 'clean', 'clean', 'walk')

    most_likely_sequence = viterbi_algorithm(states, start_probability, emission_probability, observations)

    print(most_likely_sequence)
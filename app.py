import numpy as np
import plotly.graph_objects as go
import streamlit as st
import cpp_bridge

st.set_page_config(page_title="Black-Scholes Pricing", layout="wide")

st.title("Black-Scholes Pricer")
with st.sidebar:
    st.title("Input Parameter")
    model = st.selectbox(label="Model", options=['European', 'American'])
    option_type = st.selectbox(label="Option Type", options=["Call", "Put"])
    K = st.slider(label="Strike (K)", min_value=0, max_value=1000, value=100, step=10, format="%.2f USD")
    r = st.slider(label="Risk Free (r)", min_value=0.0, max_value=0.2, value=0.03, step=0.01, format="%.2f %%")
    T = st.slider(label="Time to maturity (T)", min_value=0.01, max_value=2.0, value=0.5, step=0.01, format="%.2f year")
    sigma = st.slider(label="Volatilité", min_value=0.0, max_value=1.0, value=0.15, step=0.01, format="%.2f %%")
    S = st.number_input(label="Spot Price (S)", min_value=0, max_value=5000, value=100, step=10)
    st.button(label="Calculate")

st.write("Option Premium & Strategy Overview")
st.write("Option Premium")
if option_type == "Call":
    premium = cpp_bridge.call_price(S, K, r, sigma, T)
else:
    premium = cpp_bridge.put_price(S, K, r, sigma, T)

col1, col2 = st.columns(2)
with col1:
    st.write(f"{premium:.2f} USD")
with col2:
    if option_type == "Call":
        if S/K > 0:
            color_mode = "green"
            delta_str="In the money"
            delta_arrow="up"
        elif S/K < 0:
            color_mode = "red"
            delta_str="Out the money"
            delta_arrow="down"
        else:
            color_mode = "grey"
            delta_str="At the money"
            delta_arrow="off"
    else:
        if S/K > 0:
            color_mode = "red"
            delta_str="Out the money"
            delta_arrow="down"
        elif S/K < 0:
            color_mode = "green"
            delta_str="In the money"
            delta_arrow="up"
        else:
            color_mode = "grey"
            delta_str="At the money"
            delta_arrow="off"
    col2.metric(
    "Moneyness (S / K)",
    f"{(S/K):.3f}",
    delta=delta_str,
    delta_color=color_mode,
    delta_arrow=delta_arrow)

st.write("Hedging Schema : Protective Put Strategy")




st.write("Greeks Analysis & Interpretation")
g1, g2, g3, g4, g5 = st.columns(5)
with g1:
    st.write("Delta")
    if option_type == "Call":
        delta = cpp_bridge.delta_call(S, K, r, sigma, T)
    else:
        delta = cpp_bridge.delta_put(S, K, r, sigma, T)
    st.write(f"The option price varies by about {delta:.2f}$ when the underlying moves by +1$.")
with g2:
    st.write("Gamma")
    gamma = cpp_bridge.gamma(S, K, r, sigma, T)
    st.write(f"The option delta varies by approximately {gamma:.4f} when the underlying moves +1$.")
with g3:
    st.write("Theta")
    if option_type == "Call":
        theta = cpp_bridge.theta_call(S, K, r, sigma, T)
    else:
        theta = cpp_bridge.theta_put(S, K, r, sigma, T)
    st.write(f"The option price varies from about {theta:.2f}$ when time advances by one day.")
with g4:
    st.write("Vega")
    vega = cpp_bridge.vega(S, K, r, sigma, T)
    st.write(f"The option price varies by about {vega:.2f}$ when the implied volatility moves by +1%.")
with g5:
    st.write("Rho")
    if option_type == "Call":
        rho = cpp_bridge.rho_call(S, K, r, sigma, T)
    else:
        rho = cpp_bridge.rho_put(S, K, r, sigma, T)
    st.write(f"The call price varies by about {rho:.2f}$ when the risk-free rate moves by +1%.")
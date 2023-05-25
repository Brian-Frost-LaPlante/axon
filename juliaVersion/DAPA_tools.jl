include("damData.jl")
using Plots

Base.@kwdef mutable struct neuron
    V     :: Float32  = 0.2*rand()            # internal voltage
    Jᴱ    :: Float32  = rand()                # excitation
    Jᴵ    :: Float32  = rand()                # inhibition
    V₀    :: Float32  = rand()                # initial value for solver
    Jᴱ₀   :: Float32  = rand()                # initial value for solver
    Jᴵ₀   :: Float32  = rand()                # initial value for solver
    train :: BitArray = rand([false,true],9)  # last 9 spikes up to refractory period
    out   :: Float32  = 0                     # current output up to timescale
    w     :: Float32  = 0.5                   # kick for J
    τⱽ    :: Float32  = 18.0                  # voltage time constant
    τᴶ    :: Float32  = 5.0                   # Jᴱ and Jᴵ time constant
    Vᵀ    :: Float32  = 0.2                   # Threshold for spike
    type  :: Float32  = 1                     # ±1 for E or I neuron type
    tᵢ    :: Float32  = 0                     # internal time variable for ODE solver
    dt    :: Float32  = 0.1                   # time difference
    Tᴿ    :: Float32  = 1.0                   # refractory period
    Rᵢ    :: Float32  = rand()                # counts time since refractory period for output
    tᴿ    :: Float32  = 0                     # counts intervals of Tᴿ for train discretization
end

function guessOut(inTrain)
    guessInd = 1 + (sum(((i, x),) -> Int(x) << ((i-1) * sizeof(x)), enumerate(inTrain.chunks)))
    return damData[guessInd,9]
end

function neuronUpdate(n,inStrength)
    
    if inStrength > 0                      
        
        n.tᵢ  = n.dt
        n.Jᴱ  = n.Jᴱ + inStrength*n.w   # Neuron receives some excitatory kick
        n.Jᴱ₀ = deepcopy(n.Jᴱ)
        n.Jᴵ₀ = deepcopy(n.Jᴵ)
        n.V₀  = deepcopy(n.V)
        #n.Jᴵ  = n.Jᴵ₀ * exp(-n.tᵢ/n.τᴶ)
    
    elseif inStrength < 0
        
        n.tᵢ  = n.dt
        n.Jᴵ  = n.Jᴵ - inStrength*n.w   # Neuron receives some inhibitory kick
        n.Jᴱ₀ = deepcopy(n.Jᴱ)
        n.Jᴵ₀ = deepcopy(n.Jᴵ)
        n.V₀  = deepcopy(n.V)
        #n.Jᴱ  = n.Jᴱ₀ * exp(-n.tᵢ/n.τᴶ)
    else                                # Neuron sees nothing

        n.tᵢ  = n.tᵢ + n.dt
        n.Jᴱ  = n.Jᴱ₀ * exp(-n.tᵢ/n.τᴶ)
        n.Jᴵ  = n.Jᴵ₀ * exp(-n.tᵢ/n.τᴶ)

    end
    
    n.V  = (n.V₀ - ((n.Jᴱ₀ - n.Jᴵ₀)*n.τᴶ)/(n.τᴶ-n.τⱽ)) * exp(-n.tᵢ / n.τⱽ) + 
                    ((n.Jᴱ₀ - n.Jᴵ₀)*n.τᴶ/(n.τᴶ-n.τⱽ)) * exp(-n.tᵢ / n.τᴶ)

    if (n.V > n.Vᵀ) && (n.Rᵢ>= n.Tᴿ)    # Spike if both above threshold and ref period passed

        n.tᵢ        = 0
        n.Rᵢ        = n.dt
        n.Jᴱ₀       = deepcopy(n.Jᴱ)
        n.Jᴵ₀       = deepcopy(n.Jᴵ)
        n.V₀        = 0
        n.V         = 0
        n.out       = n.type        # the neuron spikes
        n.train[9]  = true

    else

        n.out       = 0
        n.Rᵢ        = n.Rᵢ+ n.dt          # the neuron does not spike

    end

    # we have to update the discretized spike train up to refractory periods
    
    if n.tᴿ >= n.Tᴿ
        n.tᴿ = n.dt
        n.train[1:8] = n.train[2:9]
        n.train[9]   = false
    else
        n.tᴿ = n.tᴿ + n.dt
    end

end
